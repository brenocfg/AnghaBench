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
struct v4l2_window {int global_alpha; int /*<<< orphan*/  chromakey; } ;
struct TYPE_3__ {struct v4l2_window win; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct omapvideo_info {struct omap_overlay** overlays; } ;
struct TYPE_4__ {int global_alpha; int /*<<< orphan*/  chromakey; } ;
struct omap_vout_device {int /*<<< orphan*/  lock; TYPE_2__ win; int /*<<< orphan*/  fbuf; int /*<<< orphan*/  crop; struct omapvideo_info vid_info; } ;
struct omap_overlay {int caps; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int OMAP_DSS_OVL_CAP_GLOBAL_ALPHA ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int omap_vout_new_window (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,struct v4l2_window*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_overlay(struct file *file, void *fh,
			struct v4l2_format *f)
{
	int ret = 0;
	struct omap_overlay *ovl;
	struct omapvideo_info *ovid;
	struct omap_vout_device *vout = fh;
	struct v4l2_window *win = &f->fmt.win;

	mutex_lock(&vout->lock);
	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];

	ret = omap_vout_new_window(&vout->crop, &vout->win, &vout->fbuf, win);
	if (!ret) {
		/* Video1 plane does not support global alpha on OMAP3 */
		if ((ovl->caps & OMAP_DSS_OVL_CAP_GLOBAL_ALPHA) == 0)
			vout->win.global_alpha = 255;
		else
			vout->win.global_alpha = f->fmt.win.global_alpha;

		vout->win.chromakey = f->fmt.win.chromakey;
	}
	mutex_unlock(&vout->lock);
	return ret;
}