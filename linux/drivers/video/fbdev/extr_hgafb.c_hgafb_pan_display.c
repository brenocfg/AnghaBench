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
struct fb_var_screeninfo {int vmode; int yoffset; scalar_t__ xoffset; } ;
struct TYPE_2__ {int yres_virtual; scalar_t__ xres; scalar_t__ xres_virtual; scalar_t__ yres; } ;
struct fb_info {TYPE_1__ var; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_VMODE_YWRAP ; 
 int /*<<< orphan*/  hga_pan (scalar_t__,int) ; 

__attribute__((used)) static int hgafb_pan_display(struct fb_var_screeninfo *var,
			     struct fb_info *info)
{
	if (var->vmode & FB_VMODE_YWRAP) {
		if (var->yoffset >= info->var.yres_virtual ||
		    var->xoffset)
			return -EINVAL;
	} else {
		if (var->xoffset + info->var.xres > info->var.xres_virtual
		 || var->yoffset + info->var.yres > info->var.yres_virtual
		 || var->yoffset % 8)
			return -EINVAL;
	}

	hga_pan(var->xoffset, var->yoffset);
	return 0;
}