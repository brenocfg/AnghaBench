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
struct v4l2_window {int global_alpha; } ;
struct TYPE_2__ {struct v4l2_window win; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct omapvideo_info {struct omap_overlay** overlays; } ;
struct omap_vout_device {int /*<<< orphan*/  fbuf; struct omapvideo_info vid_info; } ;
struct omap_overlay {int caps; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int OMAP_DSS_OVL_CAP_GLOBAL_ALPHA ; 
 int omap_vout_try_window (int /*<<< orphan*/ *,struct v4l2_window*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_overlay(struct file *file, void *fh,
			struct v4l2_format *f)
{
	int ret = 0;
	struct omap_vout_device *vout = fh;
	struct omap_overlay *ovl;
	struct omapvideo_info *ovid;
	struct v4l2_window *win = &f->fmt.win;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];

	ret = omap_vout_try_window(&vout->fbuf, win);

	if (!ret) {
		if ((ovl->caps & OMAP_DSS_OVL_CAP_GLOBAL_ALPHA) == 0)
			win->global_alpha = 255;
		else
			win->global_alpha = f->fmt.win.global_alpha;
	}

	return ret;
}