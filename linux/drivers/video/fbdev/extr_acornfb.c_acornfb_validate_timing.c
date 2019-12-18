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
struct fb_var_screeninfo {int pixclock; unsigned long xres; unsigned long left_margin; unsigned long right_margin; unsigned long hsync_len; unsigned long yres; unsigned long upper_margin; unsigned long lower_margin; unsigned long vsync_len; } ;
struct fb_monspecs {unsigned long vfmin; unsigned long vfmax; unsigned long hfmin; unsigned long hfmax; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
acornfb_validate_timing(struct fb_var_screeninfo *var,
			struct fb_monspecs *monspecs)
{
	unsigned long hs, vs;

	/*
	 * hs(Hz) = 10^12 / (pixclock * xtotal)
	 * vs(Hz) = hs(Hz) / ytotal
	 *
	 * No need to do long long divisions or anything
	 * like that if you factor it correctly
	 */
	hs = 1953125000 / var->pixclock;
	hs = hs * 512 /
	     (var->xres + var->left_margin + var->right_margin + var->hsync_len);
	vs = hs /
	     (var->yres + var->upper_margin + var->lower_margin + var->vsync_len);

	return (vs >= monspecs->vfmin && vs <= monspecs->vfmax &&
		hs >= monspecs->hfmin && hs <= monspecs->hfmax) ? 0 : -EINVAL;
}