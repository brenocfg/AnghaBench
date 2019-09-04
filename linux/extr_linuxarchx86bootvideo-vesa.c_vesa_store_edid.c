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

/* Variables and functions */

void vesa_store_edid(void)
{
#ifdef CONFIG_FIRMWARE_EDID
	struct biosregs ireg, oreg;

	/* Apparently used as a nonsense token... */
	memset(&boot_params.edid_info, 0x13, sizeof boot_params.edid_info);

	if (vginfo.version < 0x0200)
		return;		/* EDID requires VBE 2.0+ */

	initregs(&ireg);
	ireg.ax = 0x4f15;		/* VBE DDC */
	/* ireg.bx = 0x0000; */		/* Report DDC capabilities */
	/* ireg.cx = 0;	*/		/* Controller 0 */
	ireg.es = 0;			/* ES:DI must be 0 by spec */
	intcall(0x10, &ireg, &oreg);

	if (oreg.ax != 0x004f)
		return;		/* No EDID */

	/* BH = time in seconds to transfer EDD information */
	/* BL = DDC level supported */

	ireg.ax = 0x4f15;		/* VBE DDC */
	ireg.bx = 0x0001;		/* Read EDID */
	/* ireg.cx = 0; */		/* Controller 0 */
	/* ireg.dx = 0;	*/		/* EDID block number */
	ireg.es = ds();
	ireg.di =(size_t)&boot_params.edid_info; /* (ES:)Pointer to block */
	intcall(0x10, &ireg, &oreg);
#endif /* CONFIG_FIRMWARE_EDID */
}