#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Livre {
    int id;
    char titre[100];
    char auteur[50];
    int disponible; // 1 = oui, 0 = emprunté
    struct Livre* suivant;
};

struct Livre* bibliotheque = NULL;

// Ajouter un livre en tête de liste O(1)
void ajouterLivre() {
    struct Livre* nouveau = (struct Livre*)malloc(sizeof(struct Livre));
    printf("\nID du livre: ");
    scanf("%d", &nouveau->id);
    getchar(); // vide le buffer
    printf("Titre: ");
    fgets(nouveau->titre, 100, stdin);
    nouveau->titre[strcspn(nouveau->titre, "\n")] = 0;

    printf("Auteur: ");
    fgets(nouveau->auteur, 50, stdin);
    nouveau->auteur[strcspn(nouveau->auteur, "\n")] = 0;

    nouveau->disponible = 1;
    nouveau->suivant = bibliotheque;
    bibliotheque = nouveau;
    printf("-> Livre ajoute avec succes!\n");
}

void afficherLivres() {
    struct Livre* temp = bibliotheque;
    if(temp == NULL) { printf("\nBibliotheque vide!\n"); return; }
    printf("\n--- LISTE BIBLIOTHEQUE ---\n");
    printf("ID | TITRE | AUTEUR | ETAT\n");
    while(temp!= NULL) {
        printf("%d | %s | %s | %s\n", temp->id, temp->titre, temp->auteur,
               temp->disponible? "Dispo" : "Emprunte");
        temp = temp->suivant;
    }
}

void rechercherLivre() {
    char mot[100];
    printf("\nTitre a chercher: ");
    getchar();
    fgets(mot, 100, stdin);
    mot[strcspn(mot, "\n")] = 0;

    struct Livre* temp = bibliotheque;
    int trouve = 0;
    while(temp!= NULL) {
        if(strstr(temp->titre, mot)!= NULL) {
            printf("Trouve: %d | %s | %s\n", temp->id, temp->titre, temp->auteur);
            trouve = 1;
        }
        temp = temp->suivant;
    }
    if(!trouve) printf("Aucun livre trouve.\n");
}

void supprimerLivre() {
    int id; printf("\nID a supprimer: "); scanf("%d", &id);
    struct Livre *temp = bibliotheque, *prec = NULL;

    while(temp!= NULL && temp->id!= id) {
        prec = temp; temp = temp->suivant;
    }
    if(temp == NULL) { printf("ID introuvable!\n"); return; }

    if(prec == NULL) bibliotheque = temp->suivant;
    else prec->suivant = temp->suivant;

    free(temp);
    printf("Livre supprime!\n");
}

void emprunterLivre() {
    int id; printf("\nID a emprunter: "); scanf("%d", &id);
    struct Livre* temp = bibliotheque;
    while(temp!= NULL) {
        if(temp->id == id) {
            if(temp->disponible) { temp->disponible = 0; printf("Emprunt reussi!\n"); }
            else printf("Deja emprunte!\n");
            return;
        }
        temp = temp->suivant;
    }
    printf("Livre non trouve!\n");
}

int main() {
    int choix;
    while(1) {
        printf("\n===== GESTION BIBLIOTHEQUE - L1 GI =====\n");
        printf("1. Ajouter Livre\n");
        printf("2. Afficher tous\n");
        printf("3. Rechercher\n");
        printf("4. Emprunter\n");
        printf("5. Supprimer\n");
        printf("0. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);

        if(choix==1) ajouterLivre();
        else if(choix==2) afficherLivres();
        else if(choix==3) rechercherLivre();
        else if(choix==4) emprunterLivre();
        else if(choix==5) supprimerLivre();
        else break;
    }
    return 0;
}
