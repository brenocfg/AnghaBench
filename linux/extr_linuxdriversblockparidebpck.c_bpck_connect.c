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
struct TYPE_3__ {int mode; scalar_t__ devtype; scalar_t__ unit; int /*<<< orphan*/  saved_r0; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 scalar_t__ PI_PCD ; 
 int /*<<< orphan*/  WR (int,int) ; 
 int /*<<< orphan*/  r0 () ; 
 int /*<<< orphan*/  t2 (int) ; 
 int /*<<< orphan*/  w0 (scalar_t__) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void bpck_connect ( PIA *pi  )

{       pi->saved_r0 = r0();
	w0(0xff-pi->unit); w2(4); w0(pi->unit);
	t2(8); t2(8); t2(8); 
	t2(2); t2(2);
	
	switch (pi->mode) {

	case 0: t2(8); WR(4,0);
		break;

	case 1: t2(8); WR(4,0x10);
		break;

	case 2:
        case 3:
	case 4: w2(0); WR(4,8);
		break;

	}

	WR(5,8);

	if (pi->devtype == PI_PCD) {
		WR(0x46,0x10);		/* fiddle with ESS logic ??? */
		WR(0x4c,0x38);
		WR(0x4d,0x88);
		WR(0x46,0xa0);
		WR(0x41,0);
		WR(0x4e,8);
		}
}