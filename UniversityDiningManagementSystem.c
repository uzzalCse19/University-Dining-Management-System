#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Max_Students 20000
#define Token_Price 30

char authorityID[20] = "789";

struct student {
    char id[20];
    char name[20];
    int lunchToken;
    int dinnerToken;
    int balance;
    char password[200];
    
};

struct student Students[Max_Students];
int studentCount = 0;

void createDefaultInputFile() {
    FILE *file = fopen("students.txt", "a");  
    if (file == NULL) {
        printf("Error creating students.txt file.\n");
        exit(1);
    }
    fclose(file);
}

void loadStudentsFromFile() {
    FILE *file = fopen("students.txt", "r");
    if (file) {
        studentCount = 0;
        char line[150];
        fgets(line, sizeof(line), file);  

        while (fgets(line, sizeof(line), file)) {  
            struct student temp;
            if (sscanf(line, "%s %[^\t] %d %d %d %s", 
                       temp.id, 
                       temp.name, 
                       &temp.lunchToken, 
                       &temp.dinnerToken, 
                       &temp.balance, 
                       temp.password) == 6) {  
                Students[studentCount] = temp;
                studentCount++;
            }
        }
        fclose(file);
    } else {
        printf("File not found. Creating a new one.\n");
        createDefaultInputFile();
    }
}

void saveStudentsToFile() {
    FILE *file = fopen("students.txt", "w");
    if (file) {
        fprintf(file, "ID\tName\tLunch_Tokens\tDinner_Tokens\tBalance\tPassword\n");
        for (int i = 0; i < studentCount; i++) {
            fprintf(file, "%s\t%s\t%d\t%d\t%d\t%s\n", 
                    Students[i].id, 
                    Students[i].name, 
                    Students[i].lunchToken, 
                    Students[i].dinnerToken, 
                    Students[i].balance,
                    Students[i].password);
        }
        fclose(file);
    }
}


void addStudent() {
    char authoID[20];
    printf("Enter authority ID: ");
    scanf("%s", authoID);
    if (strcmp(authorityID, authoID) == 0) {
        struct student newStudent;
        printf("Enter Student ID: ");
        scanf("%s", newStudent.id);
        for (int i = 0; i < studentCount; i++) {
            if (strcmp(Students[i].id, newStudent.id) == 0) {
                printf("\nYou are already added.\n\n");
                return;
            }
        }
        printf("Enter Student Name: ");
        scanf(" %[^\n]%*c", newStudent.name);
        printf("Enter password: ");
        scanf("%s", newStudent.password);
        newStudent.dinnerToken = 0;
        newStudent.lunchToken = 0;
        newStudent.balance = 0;

        Students[studentCount] = newStudent;
        studentCount++;
        saveStudentsToFile();
        printf("\nStudent added successfully\n\n");
    } else {
        printf("\nPlease enter the correct Authority ID.\n\n");
    }
}

void deleteStudent() {
    char authoID[20];
    printf("Enter authority ID: ");
    scanf("%s", authoID);
     if (strcmp(authorityID, authoID) == 0) {
    char id[20];
    printf("Enter student ID to delete: ");
    scanf("%s", id);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(Students[i].id, id) == 0) {
            for (int j = i; j < studentCount - 1; j++) {
                Students[j] = Students[j + 1];
            }
            studentCount--;
            saveStudentsToFile();
            printf("\nStudent deleted successfully.\n\n");
            return;
        }
    }
    printf("\nStudent not found with ID %s.\n\n", id);
     }
     else {
        printf("\nPlease enter the correct Authority ID.\n\n");
    }

}

void updateStudent() {
    char id[20];
    printf("Enter student ID to update: ");
    scanf("%s", id);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(Students[i].id, id) == 0) {
            printf("\nCurrent record: ID: %s, Name: %s, Lunch Tokens: %d, Dinner Tokens: %d, Balance: %d\n",
                   Students[i].id, Students[i].name, Students[i].lunchToken, Students[i].dinnerToken, Students[i].balance);
            printf("Enter new Name: ");
            scanf(" %[^\n]%*c", Students[i].name);
            saveStudentsToFile();
            printf("\nUpdated successfully.\n\n");
            return;
        }
    }
    printf("\nStudent not found with ID %s.\n\n", id);
}

void searchStudent() {
    char id[20];
    printf("Enter student ID: ");
    scanf("%s", id);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(Students[i].id, id) == 0) {
            printf("\nRecord: ID: %s, Name: %s, Lunch Tokens: %d, Dinner Tokens: %d, Balance: %d\n\n",
                   Students[i].id, Students[i].name, Students[i].lunchToken, Students[i].dinnerToken, Students[i].balance);
            return;
        }
    }
    printf("\nStudent record is not found.\n\n");
}

void takeToken() {
    char id[20];
    printf("Enter student ID: ");
    scanf("%s", id);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(Students[i].id, id) == 0) {
            printf("Token Type:\n1.Lunch\n2.Dinner\n3.Both\n");
            printf("Choose token type: ");
            int choice;
            scanf("%d", &choice);
            if (choice == 1) {
                Students[i].lunchToken++;
                Students[i].balance += Token_Price;
                printf("\nLunch token taken. Total lunch tokens: %d\n\n", Students[i].lunchToken);
            } else if (choice == 2) {
                Students[i].dinnerToken++;
                Students[i].balance += Token_Price;
                printf("Dinner token taken. Total Dinner tokens: %d\n", Students[i].dinnerToken);
            } else if (choice == 3) {
                Students[i].lunchToken++;
                Students[i].dinnerToken++;
                Students[i].balance += 2 * Token_Price;
                printf("\nDinner and lunch token taken. Total lunch tokens: %d , total dinner tokens: %d\n\n", Students[i].lunchToken, Students[i].dinnerToken);
            } else {
                printf("\nInvalid choice.\n\n");
            }
            saveStudentsToFile();
            return;
        }
    }
    printf("\nStudent record not found.\n\n");
}

void payBill() {
    char id[20];
    printf("Enter student ID: ");
    scanf("%s", id);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(Students[i].id, id) == 0) {
            printf("\nYou have to pay %dtk only.\n\n", Students[i].balance);
            Students[i].balance = 0;
            saveStudentsToFile();
            return;
        }
    }
    printf("\nStudent record is not found.\n\n");
}

void takeMeal() {
    char id[20];
    printf("Enter student ID: ");
    scanf("%s", id);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(Students[i].id, id) == 0) {
            char pass[20];
            printf("Enter password: ");
            scanf("%s", pass);
            if (strcmp(Students[i].password, pass) == 0) {
                printf("\n1.Lunch\n2.Dinner\n");
                int choice;
                printf("Choose meal type: ");
                scanf("%d", &choice);
                printf("\n");
                if (choice == 1) {
                    if (Students[i].lunchToken > 0) {
                        Students[i].lunchToken--;
                        printf("Lunch taken. Remaining lunch token: %d\n\n", Students[i].lunchToken);
                    } else printf("Lunch token is not available\n\n");
                } else if (choice == 2) {
                    if (Students[i].dinnerToken > 0) {
                        Students[i].dinnerToken--;
                        printf("Dinner taken. Remaining dinner token: %d\n\n", Students[i].dinnerToken);
                    } else printf("Dinner token is not available\n\n");
                } else printf("Meal type is invalid.\n\n");
                saveStudentsToFile();
                return;
            }
        }
    }
    printf("\nPlease enter valid information.\n\n");
}

void viewAll() {
    printf("All Students:\n");
    printf("ID\tName\tLunch_Tokens\tDinner_Tokens\tBalance\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%s\t%s\t%d\t%d\t%d\n", 
               Students[i].id, 
               Students[i].name, 
               Students[i].lunchToken, 
               Students[i].dinnerToken, 
               Students[i].balance
              );
    }
    printf("\n");
}

void displayMenu() {
    printf("University Dining Management System.\n");
    printf("1. Add Student\n");
    printf("2. Delete Student\n");
    printf("3. Update Student\n");
    printf("4. Search Student\n");
    printf("5. View All Students\n");
    printf("6. Take Token\n");
    printf("7. Pay Bill\n");
    printf("8. Take Meal\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    loadStudentsFromFile();
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: addStudent(); break;
            case 2: deleteStudent(); break;
            case 3: updateStudent(); break;
            case 4: searchStudent(); break;
            case 5: viewAll(); break;
            case 6: takeToken(); break;
            case 7: payBill(); break;
            case 8: takeMeal(); break;
            case 0: saveStudentsToFile(); break;
            default: printf("Invalid choice. Please try again.\n\n");
        }
    } while (choice != 0);

    printf("Exiting program. Goodbye!\n");
    return 0;
}
