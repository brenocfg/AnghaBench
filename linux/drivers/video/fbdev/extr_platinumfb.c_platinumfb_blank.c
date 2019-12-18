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
struct fb_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int platinumfb_blank(int blank,  struct fb_info *fb)
{
/*
 *  Blank the screen if blank_mode != 0, else unblank. If blank == NULL
 *  then the caller blanks by setting the CLUT (Color Look Up Table) to all
 *  black. Return 0 if blanking succeeded, != 0 if un-/blanking failed due
 *  to e.g. a video mode which doesn't support it. Implements VESA suspend
 *  and powerdown modes on hardware that supports disabling hsync/vsync:
 *    blank_mode == 2: suspend vsync
 *    blank_mode == 3: suspend hsync
 *    blank_mode == 4: powerdown
 */
/* [danj] I think there's something fishy about those constants... */
/*
	struct fb_info_platinum *info = (struct fb_info_platinum *) fb;
	int	ctrl;

	ctrl = le32_to_cpup(&info->platinum_regs->ctrl.r) | 0x33;
	if (blank)
		--blank_mode;
	if (blank & VESA_VSYNC_SUSPEND)
		ctrl &= ~3;
	if (blank & VESA_HSYNC_SUSPEND)
		ctrl &= ~0x30;
	out_le32(&info->platinum_regs->ctrl.r, ctrl);
*/
/* TODO: Figure out how the heck to powerdown this thing! */
	return 0;
}