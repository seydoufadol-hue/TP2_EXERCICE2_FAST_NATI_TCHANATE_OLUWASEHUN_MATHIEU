#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// --- 1. Classe Matiere ---
class Matiere {
private:
    string code;
    string nom;
public:
    Matiere(string c, string n) : code(c), nom(n) {}
    string getCode() const { return code; }
    string getNom() const { return nom; }
    void afficher() const { cout << "[" << code << "] " << nom; }
};

// --- 2. Classe Etudiant ---
class Etudiant {
private:
    string numEtudiant;
    string nom;
    string prenom;
public:
    Etudiant(string num, string n, string p) : numEtudiant(num), nom(n), prenom(p) {}
    string getNumEtudiant() const { return numEtudiant; }
    string getNomComplet() const { return prenom + " " + nom; }
    void afficher() const { cout << numEtudiant << " - " << getNomComplet(); }
};

// --- 3. Classe GroupeTD ---
class GroupeTD {
private:
    string codeGroupe;
    string niveau;
    vector<Etudiant*> etudiants;
public:
    GroupeTD(string code, string niv) : codeGroupe(code), niveau(niv) {}
    string getCodeGroupe() const { return codeGroupe; }
    
    void ajouterEtudiant(Etudiant* e) {
        etudiants.push_back(e);
    }
    
    const vector<Etudiant*>& getEtudiants() const { return etudiants; }
    
    void afficher() const {
        cout << "Groupe " << codeGroupe << " (" << niveau << ") - " << etudiants.size() << " étudiants" << endl;
    }
};

// --- 4. Classe Enseignant ---
class Enseignant {
private:
    string idEnseignant;
    string nom;
    string prenom;
public:
    Enseignant(string id, string n, string p) : idEnseignant(id), nom(n), prenom(p) {}
    string getNomComplet() const { return prenom + " " + nom; }
};

// --- 5. Classe Salle ---
class Salle {
private:
    string numeroSalle;
    int capacite;
public:
    Salle(string num, int cap) : numeroSalle(num), capacite(cap) {}
    string getNumero() const { return numeroSalle; }
    int getCapacite() const { return capacite; }
};

// --- 6. Classe SeanceTD ---
class SeanceTD {
private:
    string idSeance;
    Matiere matiere;
    GroupeTD* groupe;
    Enseignant* enseignant;
    Salle salle;
    string dateHeure;
public:
    SeanceTD(string id, Matiere mat, GroupeTD* g, Enseignant* ens, Salle sal, string dh)
        : idSeance(id), matiere(mat), groupe(g), enseignant(ens), salle(sal), dateHeure(dh) {}

    void afficherDetails() const {
        cout << "\n--- Séance de TD [" << idSeance << "] ---" << endl;
        cout << "Matière   : " << matiere.getNom() << endl;
        cout << "Groupe    : " << groupe->getCodeGroupe() << endl;
        cout << "Enseignant: " << enseignant->getNomComplet() << endl;
        cout << "Salle     : " << salle.getNumero() << endl;
        cout << "Horaire   : " << dateHeure << endl;
    }
};

// --- 7. Classe Presence ---
class Presence {
private:
    Etudiant* etudiant;
    SeanceTD* seance;
    bool present;
public:
    Presence(Etudiant* e, SeanceTD* s, bool stat) : etudiant(e), seance(s), present(stat) {}
    
    void setPresent(bool p) { present = p; }
    bool estPresent() const { return present; }

    void afficherBilan() const {
        // CORRECTION EFFECTUÉE ICI : suppression du "->" parasite avant le "<<"
        cout << "Étudiant: " << etudiant->getNomComplet() 
             << " | Statut: " << (present ? "PRESENT(E)" : "ABSENT(E)") << endl;
    }
};

// --- Programme Principal de Test ---
int main() {
    // Création des ressources de base
    Matiere math("MATH101", "Algèbre Linéaire");
    Enseignant ens1("E01", "TCHOMINA", "Cédric");
    Salle salle1("Amphi A", 150);

    // Création d'un groupe de TD (ex: MI1)
    GroupeTD groupeMI1("MI1", "L1");

    // Inscription des étudiants
    Etudiant e1("ETD01", "MATHIEU", "TCHANATE");
    Etudiant e2("ETD02", "HOUANDJA", "Laurence");
    
    groupeMI1.ajouterEtudiant(&e1);
    groupeMI1.ajouterEtudiant(&e2);

    // Programmation d'une séance de TD
    SeanceTD seance1("S001", math, &groupeMI1, &ens1, salle1, "Lundi 14h-16h");
    seance1.afficherDetails();

    // Enregistrement des présences
    cout << "\n--- Suivi des Présences ---" << endl;
    Presence p1(&e1, &seance1, true);   // Adio est présent
    Presence p2(&e2, &seance1, false);  // Laurence est absente

    p1.afficherBilan();
    p2.afficherBilan();

    return 0;
}
