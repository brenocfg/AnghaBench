#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omapfb_update_window {int x; int y; int out_x; int out_y; int width; int height; int out_width; int out_height; } ;
struct omapfb_plane_struct {struct omapfb_device* fbdev; } ;
struct omapfb_device {TYPE_2__* ctrl; TYPE_1__* panel; } ;
struct fb_var_screeninfo {int rotate; } ;
struct fb_info {struct fb_var_screeninfo var; struct omapfb_plane_struct* par; } ;
struct TYPE_4__ {int (* update_window ) (struct fb_info*,struct omapfb_update_window*,void (*) (void*),void*) ;scalar_t__ (* get_update_mode ) () ;} ;
struct TYPE_3__ {int x_res; int y_res; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ OMAPFB_MANUAL_UPDATE ; 
 scalar_t__ stub1 () ; 
 int stub2 (struct fb_info*,struct omapfb_update_window*,void (*) (void*),void*) ; 

int omapfb_update_window_async(struct fb_info *fbi,
				struct omapfb_update_window *win,
				void (*callback)(void *),
				void *callback_data)
{
	int xres, yres;
	struct omapfb_plane_struct *plane = fbi->par;
	struct omapfb_device *fbdev = plane->fbdev;
	struct fb_var_screeninfo *var = &fbi->var;

	switch (var->rotate) {
	case 0:
	case 180:
		xres = fbdev->panel->x_res;
		yres = fbdev->panel->y_res;
		break;
	case 90:
	case 270:
		xres = fbdev->panel->y_res;
		yres = fbdev->panel->x_res;
		break;
	default:
		return -EINVAL;
	}

	if (win->x >= xres || win->y >= yres ||
	    win->out_x > xres || win->out_y > yres)
		return -EINVAL;

	if (!fbdev->ctrl->update_window ||
	    fbdev->ctrl->get_update_mode() != OMAPFB_MANUAL_UPDATE)
		return -ENODEV;

	if (win->x + win->width > xres)
		win->width = xres - win->x;
	if (win->y + win->height > yres)
		win->height = yres - win->y;
	if (win->out_x + win->out_width > xres)
		win->out_width = xres - win->out_x;
	if (win->out_y + win->out_height > yres)
		win->out_height = yres - win->out_y;
	if (!win->width || !win->height || !win->out_width || !win->out_height)
		return 0;

	return fbdev->ctrl->update_window(fbi, win, callback, callback_data);
}