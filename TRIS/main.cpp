/*
 se in griglia c'e' ZERO cella vuota
 se in griglia c'e' UNO stiamo parlando di una X (giocatore 1)
 se in griglia c'e' DUE stiamo parlando di un CERCHIO (giocatore 2)
*/

#include <iostream>

using namespace std;

class Tris
{
public:
    int griglia[3][3];

    void reset_tabella()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                griglia[i][j] = 0;
            }
        }
    }

    void stampa_griglia()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << griglia[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void stampa_griglia_avanzato()
    {
        cout << "+---+---+---+" << endl;
        
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << "|";
                if(griglia[i][j] == 0)
                    cout << "   ";
                else if (griglia[i][j] == 1)
                    cout << " X ";
                else if (griglia[i][j] == 2)
                    cout << " O ";
                else
                    cout << " E ";
            }
            cout << "|" << endl;
            cout << "+---+---+---+" << endl;
        }
    }

    bool giocatore_uno(int x, int y)
    {
        if (x > 2 || x < 0)
            return false;

        if (y > 2 || y < 0)
            return false;

        if (griglia[x][y] == 1 || griglia[x][y] == 2)
            return false;

        griglia[x][y] = 1;
        return true;
    }

    bool giocatore_due(int x, int y)
    {
        if (x > 2 || x < 0)
            return false;

        if (y > 2 || y < 0)
            return false;

        if (griglia[x][y] == 1 || griglia[x][y] == 2)
            return false;

        griglia[x][y] = 2;
        return true;
    }

    int controlla_vincitore()
    {
        int risultato;
        for (int i = 0; i < 3; i++)
        {
            risultato = controlla_collonna(i);
            if (risultato != 0)
                return risultato;

            risultato = controlla_riga(i);
            if (risultato != 0)
                return risultato;
        }
        return controlla_diagonali();
    }

private:
    int controlla_collonna(int col)
    {
        int acc_uno = 0;
        int acc_due = 0;
        for (int i = 0; i < 3; i++)
        {
            int cella = griglia[i][col];
            if (cella == 1)
                acc_uno++;
            else if (cella == 2)
                acc_due++;
        }

        if (acc_uno == 3)
            return 1;
        if (acc_due == 3)
            return 2;
        return 0;
    }

    int controlla_riga(int riga)
    {
        int acc_uno = 0;
        int acc_due = 0;
        for (int i = 0; i < 3; i++)
        {
            int cella = griglia[riga][i]; // unica differenza con il metono precedente
            if (cella == 1)
                acc_uno++;
            else if (cella == 2)
                acc_due++;
        }

        if (acc_uno == 3)
            return 1;
        if (acc_due == 3)
            return 2;
        return 0;
    }

    int controlla_diagonali() // @TODO: Manca l'implementazione
    {
        return 0;
    }
};

int main(int argc, char const *argv[])
{
    Tris myTris;

    myTris.reset_tabella();

    cout << "Stato iniziale!" << endl;
    // myTris.stampa_griglia();
    myTris.stampa_griglia_avanzato();

    int x, y;
    bool mossa_valida;
    int vincitore;
    int mosse_totali = 0;

    while (mosse_totali < 9) // @TODO: controllare se funziona anche nel caso di parità
    {
        do
        {
            cout << "Mossa del giocatore 1." << endl;
            cout << "x: ";
            cin >> x;

            cout << "y: ";
            cin >> y;

            mossa_valida = myTris.giocatore_uno(y, x);
        } while (!mossa_valida);

        //myTris.stampa_griglia();
        myTris.stampa_griglia_avanzato();

        vincitore = myTris.controlla_vincitore();
        if(vincitore != 0)
            break;
        
        // Controllo se ci sono delle mosse rimanenti nella griglia
        mosse_totali++;    
        if(mosse_totali >= 9)
            break;

        do
        {
            cout << "Mossa del giocatore 2." << endl;
            cout << "x: ";
            cin >> x;

            cout << "y: ";
            cin >> y;

            mossa_valida = myTris.giocatore_due(y, x);
        } while (!mossa_valida);

        //myTris.stampa_griglia();
        myTris.stampa_griglia_avanzato();

        vincitore = myTris.controlla_vincitore();
        if(vincitore != 0)
            break;
        mosse_totali++;
    }


    if(vincitore == 1)
        cout << "Vince giocatore 1!" << endl;
    else if(vincitore == 2)
        cout << "Vince giocatore 2!" << endl;
    else
        cout << "Pareggio!" << endl;

    return 0;
}
