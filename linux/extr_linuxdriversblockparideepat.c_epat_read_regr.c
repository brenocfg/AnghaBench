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
 int* cont_map ; 
 int j44 (int,int) ; 
 int j53 (int,int) ; 
 int r0 () ; 
 int r1 () ; 
 int r2 () ; 
 int r4 () ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 
 int /*<<< orphan*/  w3 (int) ; 

__attribute__((used)) static int epat_read_regr( PIA *pi, int cont, int regr )

{	int  a, b, r;

	r = regr + cont_map[cont];

	switch (pi->mode) {

	case 0:	w0(r); w2(1); w2(3); 
		a = r1(); w2(4); b = r1();
		return j44(a,b);

	case 1: w0(0x40+r); w2(1); w2(4);
		a = r1(); b = r2(); w0(0xff);
		return j53(a,b);

	case 2: w0(0x20+r); w2(1); w2(0x25);
		a = r0(); w2(4);
		return a;

	case 3:
	case 4:
	case 5: w3(r); w2(0x24); a = r4(); w2(4);
		return a;

	}
	return -1;	/* never gets here */
}