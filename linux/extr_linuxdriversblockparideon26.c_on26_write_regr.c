#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  P1 ; 
 int /*<<< orphan*/  P2 ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 
 int /*<<< orphan*/  w3 (int) ; 
 int /*<<< orphan*/  w4 (int) ; 

__attribute__((used)) static void on26_write_regr( PIA *pi, int cont, int regr, int val )

{       int  r;

        r = (regr<<2) + 1 + cont;

        switch (pi->mode)  {

        case 0:
        case 1: w0(1); P1; w0(r); P2; w0(0); P1;
		w0(val); P2; w0(val); P2;
		break;

	case 2:
	case 3:
        case 4: w3(1); w3(1); w2(5); w4(r); w2(4);
		w3(0); w3(0); 
		w2(5); w4(val); w2(4);
		w2(5); w4(val); w2(4);
                break;
        }
}