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
struct cirrusfb_info {scalar_t__ btype; int /*<<< orphan*/  regbase; } ;

/* Variables and functions */
 scalar_t__ BT_PICASSO ; 
 int VGA_PEL_D ; 
 int VGA_PEL_IR ; 
 unsigned char vga_r (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static unsigned char RGen(const struct cirrusfb_info *cinfo, int regnum)
{
	unsigned long regofs = 0;

	if (cinfo->btype == BT_PICASSO) {
		/* Picasso II specific hack */
/*	      if (regnum == VGA_PEL_IR || regnum == VGA_PEL_D ||
		  regnum == CL_VSSM2) */
		if (regnum == VGA_PEL_IR || regnum == VGA_PEL_D)
			regofs = 0xfff;
	}

	return vga_r(cinfo->regbase, regofs + regnum);
}