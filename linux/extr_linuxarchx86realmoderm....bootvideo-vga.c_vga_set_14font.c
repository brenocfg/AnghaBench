#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct biosregs {int ax; int bl; int cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  initregs (struct biosregs*) ; 
 int /*<<< orphan*/  intcall (int,struct biosregs*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vga_set_14font(void)
{
	/* Set 9x14 font - 80x28 on VGA */
	struct biosregs ireg;

	initregs(&ireg);

	/* Set 9x14 font */
	ireg.ax = 0x1111;
	/* ireg.bl = 0; */
	intcall(0x10, &ireg, NULL);

	/* Turn off cursor emulation */
	ireg.ax = 0x1201;
	ireg.bl = 0x34;
	intcall(0x10, &ireg, NULL);

	/* Cursor is scan lines 11-12 */
	ireg.ax = 0x0100;
	ireg.cx = 0x0b0c;
	intcall(0x10, &ireg, NULL);
}