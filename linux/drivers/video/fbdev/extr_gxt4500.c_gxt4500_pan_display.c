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
struct gxt4500_par {int dummy; } ;
struct fb_var_screeninfo {int xoffset; int yoffset; } ;
struct TYPE_2__ {scalar_t__ xres; scalar_t__ xres_virtual; scalar_t__ yres; scalar_t__ yres_virtual; } ;
struct fb_info {TYPE_1__ var; struct gxt4500_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REFRESH_START ; 
 int /*<<< orphan*/  writereg (struct gxt4500_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gxt4500_pan_display(struct fb_var_screeninfo *var,
			       struct fb_info *info)
{
	struct gxt4500_par *par = info->par;

	if (var->xoffset & 7)
		return -EINVAL;
	if (var->xoffset + info->var.xres > info->var.xres_virtual ||
	    var->yoffset + info->var.yres > info->var.yres_virtual)
		return -EINVAL;

	writereg(par, REFRESH_START, (var->xoffset << 16) | var->yoffset);
	return 0;
}