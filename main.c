/*
    Alumno: Daniela Vignau León
    Fecha: 27 de agosto de 2020
    Materia: Programación Avanzada
    Profesor: Vicente Cubells
    Tarea 2: Apuntadores a funciones
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char * title;
    int pages;
} book;

void main_menu();
void traverse_integers();
void traverse_books();

typedef void (*t_print)(void *);
typedef void (*t_direction)(void *, size_t, size_t, t_print);
typedef void (*t_iterator)(void *, size_t, size_t, t_print);

void iterate(void *, size_t, size_t, t_print, t_iterator);

void traverse(t_iterator, void *, size_t, size_t, t_print);
void forward(void *, size_t, size_t, t_print);
void backward(void *, size_t, size_t, t_print);
void bidirectional(void *, size_t, size_t, t_print);

void move(t_direction, void *, size_t, size_t, t_print);
void begin(void *, size_t, size_t, t_print);
void next(void *, size_t, size_t, t_print);
void prev(void *, size_t, size_t, t_print);

void free_books(book *, int);

void print_numbers(void *);
void print_books(void *);

int main(int argc, char const *argv[]) {
    main_menu();
    return 0;
}

void main_menu() {
    int option = 0;
    while(option != 3) {
        printf("-------------------------------------------------------");
        printf("\n\t     Traverse over a set of elements\n");
        printf("-------------------------------------------------------\n\n");
        printf("\t1 - Numbers\n\t2 - Books\n\t3 - Exit\n\n");
        printf("Select an option (1-3): ");
        scanf("%d", &option);
        switch(option) {
            case 1: 
                traverse_integers();
                break;
            case 2:
                traverse_books();
                break; 
            case 3: 
                printf("\n\n------------------- Exiting Program -------------------\n\n");
                exit(0);
            default:
                printf("\nThat option does not exist. Try again\n");
                break;
        }    
    }
}

void traverse_integers() {
    printf("\n\n----------------------- Numbers -----------------------");
    int option = 0;
    int option2 = 0;
    printf("\nType in the number (n) of elements you wish to create. \nThe elements will be created consecutively from 0 to n.\nType in -1 to go back: ");
    scanf("%d", &option);

    if(option == -1 || option == 0) {
        printf("\n\nGoing back to main menu\n\n");
    } else {
        int n = option;
        int * vector = (int *) malloc(sizeof(int) * n);
        int * aux = vector;
        int * final = vector + n;
        int cont = 0;

        for(; aux < final; ++aux) {
            *aux = cont;
            cont ++;
        }

        while(option2 != 4) {
            printf("\n\t1 - Forward\n\t2 - Backward\n\t3 - Bidirectional\n\t4 - Iterate over elements \n\t5 - Back to main menu\n\t6 - Exit program\n");
            printf("\nSelect an option (1-6): ");
            scanf("%d", &option2);

            switch(option2) {
                case 1:
                    printf("\nForward\n");
                    printf("-------------------------------------------------------\n");
                    traverse(&forward, vector, n, sizeof(*vector), &print_numbers);
                    printf("\n-------------------------------------------------------\n\n"); 
                    break;
                case 2:
                    printf("\nBackward\n");
                    printf("-------------------------------------------------------\n");
                    traverse(&backward, vector, n, sizeof(*vector), &print_numbers);
                    printf("\n-------------------------------------------------------\n\n"); 
                break;
                case 3:
                    printf("\nBidirectional\n");
                    printf("-------------------------------------------------------\n");
                    traverse(&bidirectional, vector, n, sizeof(*vector), &print_numbers);
                    printf("\n-------------------------------------------------------\n\n"); 
                break;
                case 4:
                    printf("\n\n------------- Iterate elements one by one -------------\n\n");
                    iterate(vector, n, sizeof(*vector), &print_numbers, &forward);
                break;
                case 5: 
                    printf("\n\n------------------ Back to Main Menu ------------------\n\n");    
                    free(vector);
                    main_menu();
                    break;
                case 6: 
                    printf("\n\n------------------- Exiting Program -------------------\n\n");                
                    free(vector);
                    exit(0); 
                break; 
                default:
                printf("\nThat option does not exist. Try again\n");
                break;

            }
        }
        free(vector);
    }
    main_menu();

}

void traverse_books() {
    printf("\n\n----------------------- Books -----------------------");
    int option = 0;
    int option2 = 0;
    printf("\nType in the number of books you wish to create.\nYou will fill out both the title and number of\npages for each of the books. Type in -1 to go back.\n\nNumber of books: ");
    scanf("%d", &option);

    if(option == -1 || option == 0) {
        printf("\n\nGoing back to main menu\n\n");
    } else {
        int n = option;
        int books = 1;
        book * vector = (book *) malloc(sizeof(book) * n);
        book * aux = vector;
        book * final = vector + n;

        for(; aux < final; ++aux) {
            printf("\n----------------------- Book %d -----------------------\n", books);
            aux->title = (char *) malloc(sizeof(char) * 30);
            printf("\nBook title: ");
            scanf(" %[^\n]", aux->title);

            printf("Number of pages: ");
            scanf("%d", &aux->pages);
            books++;
        }

        while(option2 != 4) {
            printf("\n\t1 - Forward\n\t2 - Backward\n\t3 - Bidirectional\n\t4 - Iterate over elements \n\t5 - Back to main menu\n\t6- Exit program\n");
            printf("\nSelect an option (1-5): ");
            scanf("%d", &option2);

            switch(option2) {
                case 1:
                    printf("\nForward\n");
                    printf("-------------------------------------------------------\n");
                    traverse(&forward, vector, n, sizeof(*vector), &print_books);
                    printf("\n-------------------------------------------------------\n\n"); 
                    break;
                case 2:
                    printf("\nBackward\n");
                    printf("-------------------------------------------------------\n");
                    traverse(&backward, vector, n, sizeof(*vector), &print_books);
                    printf("\n-------------------------------------------------------\n\n"); 
                break;
                case 3:
                    printf("\nBidirectional\n");
                    printf("-------------------------------------------------------\n");
                    traverse(&bidirectional, vector, n, sizeof(*vector), &print_books);
                    printf("\n-------------------------------------------------------\n\n"); 
                break;
                case 4:
                    printf("\n\n------------- Iterate elements one by one -------------\n\n");
                    iterate(vector, n, sizeof(*vector), &print_books, &forward);
                break;
                case 5: 
                    printf("\n\n------------------ Back to Main Menu ------------------\n\n");    
                    free_books(vector, n);
                    main_menu();
                    break;
                case 6: 
                    printf("\n\n------------------- Exiting Program -------------------\n\n");                
                    free_books(vector, n);
                    exit(0); 
                default:
                printf("\nThat option does not exist. Try again\n");
                break;

            }
        }
        free_books(vector, n);
    }
    main_menu();
}

void iterate(void * vector, size_t n, size_t size, t_print print, t_iterator it) {
    int option = 0;
    int ctrl_fwd = 0;
    int ctrl_bwd = n;
    int at_end = 0;
    void * forward = vector;
    void * backward = vector  + (size * n - size);

    while(option != 6) {

        printf("List of elements: \n\n");
        traverse(it, vector, n, size, print);
        printf("\n\n");
        
        printf("\t1 - First element\n\t2 - Last element\n\t3 - Next element\n\t4 - Previous element\n\t5 - Back to main menu\n\t6 - Exit program\n");
        printf("\nSelect an option (1-6): ");
        scanf("%d", &option);
        
        switch(option) {
            case 1: 
                printf("\n-------------------------------------------------------\n"); 
                printf("First element: ");
                move(&begin, vector, n, sizeof(*vector), print);
                printf("\n-------------------------------------------------------\n\n"); 
                break;
            case 2:
                printf("\n-------------------------------------------------------\n");  
                printf("Last element: ");              
                void * end = vector  + (size * n - size);
                (*print)(end);
                printf("\n-------------------------------------------------------\n\n"); 
                break; 
            case 3:
                printf("\n-------------------------------------------------------\n");  
                printf("Next element: ");
                if(ctrl_fwd != n){
                    move(&next, forward, n, sizeof(*vector), print);
                    forward += size;
                    ctrl_fwd++;
                } else {
                    printf("NULL\n");
                    printf("\nThe next time you select option 3, the iteration will\nstart at the beginning\n");
                    forward = vector;
                    ctrl_fwd = 0;
                }
                printf("\n-------------------------------------------------------\n\n"); 
                break; 
            case 4:
                printf("\n-------------------------------------------------------\n");  
                printf("Previous element: ");
                if(at_end == 0){
                    if(ctrl_bwd <= n) {
                        move(&prev, backward, n, sizeof(*vector), print);
                        backward -= size;
                        ctrl_bwd--;
                        if(ctrl_bwd == 0) {
                            at_end = 1;
                        }
                    }
                } else {
                    printf("NULL\n");
                    printf("\nThe next time you select option 4, the iteration will\nstart at the end\n");
                    backward = vector  + (size * n - size);
                    ctrl_bwd = n;
                    at_end = 0;
                }
                printf("\n-------------------------------------------------------\n\n"); 
                break; 
            case 5: 
                printf("\n\n------------------ Back to Main Menu ------------------\n\n");    
                free(vector);
                main_menu();    
                break;
            case 6:
                printf("\n\n------------------- Exiting Program -------------------\n\n");                
                free(vector);
                exit(0);
            default:
                printf("\nThat option does not exist. Try again\n");
                break;
        }   
    }
    main_menu();


}

void print_numbers(void * element) {
    int * print = (int *) element;
    printf(" %2d ", *print);   
}

void print_books(void * element) {
    book * print = (book *) element;
    printf("\t%s, p. %d\n", print->title, print->pages);   
}

void free_books(book * vector, int n) {
    book * aux = vector;
    book * final = vector + n;
    for(; aux < final; ++aux) {
        free(aux->title);
    }
    free(vector);
}

void traverse(t_iterator iterator, void * vector, size_t n, size_t size, t_print print) {
    (*iterator)(vector, n, size, print);
}

void forward(void * vector, size_t n, size_t size, t_print print) {
    void * inicio = vector;
    void * final = vector + (size * n);
    while(inicio < final) {
        (*print)(inicio);
        inicio+=size;
    }
}

void backward(void * vector, size_t n, size_t size, t_print print) {
    void * inicio = vector  + (size * n - size);
    void * final = vector;

    while(inicio >= final) {
        (*print)(inicio);
        inicio -= size;
    }

}

void bidirectional(void * vector, size_t n, size_t size, t_print print) {
    void * inicio = vector;
    void * final = vector  + (size * n - size);

    while(inicio <= final) {
        if(inicio != final) {
            (*print)(inicio);
            (*print)(final);
            inicio += size;
            final -= size;

        } else {
            (*print)(inicio);
            break;
        }
    }

}

void move(t_direction direction, void * vector, size_t n, size_t size, t_print print) {
    (*direction)(vector, n, size, print);
}

void begin(void * vector, size_t n, size_t size, t_print print) {
    (*print)(vector);
}

void next(void * vector, size_t n, size_t size, t_print print) {
    (*print)(vector);
}

void prev(void * vector, size_t n, size_t size, t_print print) {
    (*print)(vector);
}