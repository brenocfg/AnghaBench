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
struct mmpfb_info {int /*<<< orphan*/  overlay; scalar_t__ fb_start_dma; TYPE_1__* fb_info; } ;
struct mmp_addr {scalar_t__* phys; } ;
struct fb_var_screeninfo {int yoffset; int xres_virtual; int xoffset; int bits_per_pixel; } ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_2__ {struct fb_var_screeninfo var; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mmp_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmp_overlay_set_addr (int /*<<< orphan*/ ,struct mmp_addr*) ; 
 int /*<<< orphan*/  mmp_overlay_set_onoff (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmpfb_set_win (TYPE_1__*) ; 

__attribute__((used)) static void mmpfb_power(struct mmpfb_info *fbi, int power)
{
	struct mmp_addr addr;
	struct fb_var_screeninfo *var = &fbi->fb_info->var;

	/* for power on, always set address/window again */
	if (power) {
		/* set window related info */
		mmpfb_set_win(fbi->fb_info);

		/* set address always */
		memset(&addr, 0, sizeof(addr));
		addr.phys[0] = fbi->fb_start_dma +
			(var->yoffset * var->xres_virtual + var->xoffset)
			* var->bits_per_pixel / 8;
		mmp_overlay_set_addr(fbi->overlay, &addr);
	}
	mmp_overlay_set_onoff(fbi->overlay, power);
}