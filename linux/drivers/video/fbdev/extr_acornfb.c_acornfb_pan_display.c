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
typedef  scalar_t__ u_int ;
struct fb_var_screeninfo {scalar_t__ yoffset; int vmode; } ;
struct TYPE_2__ {scalar_t__ yres; scalar_t__ yres_virtual; } ;
struct fb_info {TYPE_1__ var; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_VMODE_YWRAP ; 
 int /*<<< orphan*/  acornfb_update_dma (struct fb_info*,struct fb_var_screeninfo*) ; 

__attribute__((used)) static int
acornfb_pan_display(struct fb_var_screeninfo *var, struct fb_info *info)
{
	u_int y_bottom = var->yoffset;

	if (!(var->vmode & FB_VMODE_YWRAP))
		y_bottom += info->var.yres;

	if (y_bottom > info->var.yres_virtual)
		return -EINVAL;

	acornfb_update_dma(info, var);

	return 0;
}