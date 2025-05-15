#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 32
#define FILENAME "reservations.txt"

typedef struct {
    int seat_no;
    char name[50];
} Reservation;

void view_seats(int seats[]) {
    printf("\n--- Seat Availability ---\n");
    for (int i = 1; i <= MAX_SEATS; i++) {
        printf("Seat %2d: %s\n", i, seats[i] ? "Booked" : "Available");
    }
}

void load_reservations(int seats[]) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) return;

    Reservation r;
    while (fread(&r, sizeof(Reservation), 1, file)) {
        seats[r.seat_no] = 1;
    }
    fclose(file);
}

void save_reservation(Reservation r) {
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        printf("Error saving reservation.\n");
        return;
    }
    fwrite(&r, sizeof(Reservation), 1, file);
    fclose(file);
}

void reserve_seat(int seats[]) {
    Reservation r;
    printf("Enter your name: ");
    scanf(" %[^\n]", r.name);

    view_seats(seats);
    printf("\nEnter seat number to reserve (1-%d): ", MAX_SEATS);
    scanf("%d", &r.seat_no);

    if (r.seat_no < 1 || r.seat_no > MAX_SEATS) {
        printf("Invalid seat number.\n");
        return;
    }

    if (seats[r.seat_no]) {
        printf("Sorry, seat %d is already booked.\n", r.seat_no);
        return;
    }

    seats[r.seat_no] = 1;
    save_reservation(r);
    printf("Reservation successful! Seat %d is booked for %s.\n", r.seat_no, r.name);
}

void view_bookings() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("No bookings found.\n");
        return;
    }

    Reservation r;
    printf("\n--- Booked Tickets ---\n");
    while (fread(&r, sizeof(Reservation), 1, file)) {
        printf("Seat %2d - %s\n", r.seat_no, r.name);
    }
    fclose(file);
}

int main() {
    int choice;
    int seats[MAX_SEATS + 1] = {0};

    load_reservations(seats);

    do {
        printf("\n=== Bus Reservation System ===\n");
        printf("1. View Seats\n");
        printf("2. Reserve Seat\n");
        printf("3. View Bookings\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: view_seats(seats); break;
            case 2: reserve_seat(seats); break;
            case 3: view_bookings(); break;
            case 4: printf("Thank you for using the system!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
