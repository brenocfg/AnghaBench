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
struct vmw_fb_par {scalar_t__ fb_x; scalar_t__ fb_y; int /*<<< orphan*/  bo_mutex; TYPE_1__* set_fb; } ;
struct fb_var_screeninfo {scalar_t__ xoffset; scalar_t__ xres; scalar_t__ xres_virtual; scalar_t__ yoffset; scalar_t__ yres; scalar_t__ yres_virtual; } ;
struct fb_info {struct vmw_fb_par* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_fb_dirty_mark (struct vmw_fb_par*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmw_fb_pan_display(struct fb_var_screeninfo *var,
			      struct fb_info *info)
{
	struct vmw_fb_par *par = info->par;

	if ((var->xoffset + var->xres) > var->xres_virtual ||
	    (var->yoffset + var->yres) > var->yres_virtual) {
		DRM_ERROR("Requested panning can not fit in framebuffer\n");
		return -EINVAL;
	}

	mutex_lock(&par->bo_mutex);
	par->fb_x = var->xoffset;
	par->fb_y = var->yoffset;
	if (par->set_fb)
		vmw_fb_dirty_mark(par, par->fb_x, par->fb_y, par->set_fb->width,
				  par->set_fb->height);
	mutex_unlock(&par->bo_mutex);

	return 0;
}