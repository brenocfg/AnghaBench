#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct biosregs {int ah; int ax; int /*<<< orphan*/  al; } ;
struct TYPE_2__ {int /*<<< orphan*/  kbd_status; } ;

/* Variables and functions */
 TYPE_1__ boot_params ; 
 int /*<<< orphan*/  initregs (struct biosregs*) ; 
 int /*<<< orphan*/  intcall (int,struct biosregs*,struct biosregs*) ; 

__attribute__((used)) static void keyboard_init(void)
{
	struct biosregs ireg, oreg;
	initregs(&ireg);

	ireg.ah = 0x02;		/* Get keyboard status */
	intcall(0x16, &ireg, &oreg);
	boot_params.kbd_status = oreg.al;

	ireg.ax = 0x0305;	/* Set keyboard repeat rate */
	intcall(0x16, &ireg, NULL);
}