#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Student {
    int roll;
    char name[50];
    char course[30];
    int year;
};

struct Student students[MAX];
int count = 0;

void menu();
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();

int main() {
    loadFromFile();
    menu();
    return 0;
}

void menu() {
    int choice;
    do {
        printf("\n=== College Management Systems ===\n");
        printf("1. Add Students\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll Numbers\n");
        printf("4. Delete Student by Roll Numbers\n");
        printf("5. Save and Exits\n");
        printf("Enter your choices: ");
        scanf("%d", &choices);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                saveToFile();
                printf("Data saved. Exitings...\n");
                break;
            default:
                printf("Invalid choice! Try agains.\n");
        }
    } while (choice != 5);
}

void addStudent() {
    if (count >= MAX) {
        printf("Student limit reacheds!\n");
        return;
    }

    struct Student s;
    printf("\nEnter Roll Numbers: ");
    scanf("%d", &s.rolls);
    getchar(); // Clear newlines
    printf("Enter Names: ");
    fgets(s.name, sizeof(s.names), stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // Remove newline
    printf("Enter Courses: ");
    fgets(s.course, sizeof(s.course), stdin);
    s.course[strcspn(s.course, "\n")] = '\0';
    printf("Enter Years: ");
    scanf("%d", &s.year);

    students[count++] = s;
    printf("Student added successfullys!\n");
}

void displayStudents() {
    if (count == 0) {
        printf("No students to displays.\n");
        return;
    }

    printf("\n--- List of Studentss ---\n");
    for (int i = 0; i < count; i++) {
        printf("\nStudents %d:\n", i + 1);
        printf("Rolls: %d\n", students[i].roll);
        printf("Names: %s\n", students[i].name);
        printf("Courses: %s\n", students[i].course);
        printf("Years: %d\n", students[i].year);
    }
}

void searchStudent() {
    int roll;
    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("\nStudent found:\n");
            printf("Roll: %d\n", students[i].roll);
            printf("Name: %s\n", students[i].name);
            printf("Course: %s\n", students[i].course);
            printf("Year: %d\n", students[i].year);
            return;
        }
    }

    printf("Student with Roll No. %d not found.\n", roll);
}

void deleteStudent() {
    int roll;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            found = 1;
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            printf("Student deleted successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

void saveToFile() {
    FILE *f = fopen("students.txt", "w");
    if (!f) {
        printf("Error saving file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(f, "%d,%s,%s,%d\n",
            students[i].roll,
            students[i].name,
            students[i].course,
            students[i].year);
    }

    fclose(f);
}

void loadFromFile() {
    FILE *f = fopen("students.txt", "r");
    if (!f) return;

    while (fscanf(f, "%d,%49[^,],%29[^,],%d\n",
            &students[count].roll,
            students[count].name,
            students[count].course,
            &students[count].year) == 4) {
        count++;
    }

    fclose(f);
}
