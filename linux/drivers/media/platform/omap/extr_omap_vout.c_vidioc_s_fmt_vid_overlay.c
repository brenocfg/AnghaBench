#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct v4l2_window {scalar_t__ global_alpha; } ;
struct TYPE_6__ {struct v4l2_window win; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct omapvideo_info {struct omap_overlay** overlays; } ;
struct TYPE_8__ {int /*<<< orphan*/  chromakey; scalar_t__ global_alpha; } ;
struct TYPE_9__ {int flags; } ;
struct omap_vout_device {TYPE_4__ win; TYPE_5__ fbuf; int /*<<< orphan*/  crop; struct omapvideo_info vid_info; } ;
struct omap_overlay_manager_info {int trans_enabled; int trans_key_type; int /*<<< orphan*/  trans_key; } ;
struct omap_overlay {int caps; TYPE_2__* manager; } ;
struct file {int dummy; } ;
typedef  enum omap_dss_trans_key_type { ____Placeholder_omap_dss_trans_key_type } omap_dss_trans_key_type ;
struct TYPE_7__ {scalar_t__ (* set_manager_info ) (TYPE_2__*,struct omap_overlay_manager_info*) ;int /*<<< orphan*/  (* get_manager_info ) (TYPE_2__*,struct omap_overlay_manager_info*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int OMAP_DSS_COLOR_KEY_GFX_DST ; 
 int OMAP_DSS_COLOR_KEY_VID_SRC ; 
 int OMAP_DSS_OVL_CAP_GLOBAL_ALPHA ; 
 int V4L2_FBUF_FLAG_CHROMAKEY ; 
 int V4L2_FBUF_FLAG_SRC_CHROMAKEY ; 
 int omap_vout_new_window (int /*<<< orphan*/ *,TYPE_4__*,TYPE_5__*,struct v4l2_window*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct omap_overlay_manager_info*) ; 
 scalar_t__ stub2 (TYPE_2__*,struct omap_overlay_manager_info*) ; 
 struct omap_vout_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_overlay(struct file *file, void *fh,
			struct v4l2_format *f)
{
	int ret = 0;
	struct omap_overlay *ovl;
	struct omapvideo_info *ovid;
	struct omap_vout_device *vout = video_drvdata(file);
	struct v4l2_window *win = &f->fmt.win;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];

	ret = omap_vout_new_window(&vout->crop, &vout->win, &vout->fbuf, win);
	if (!ret) {
		enum omap_dss_trans_key_type key_type =
			OMAP_DSS_COLOR_KEY_GFX_DST;
		int enable;

		/* Video1 plane does not support global alpha on OMAP3 */
		if (ovl->caps & OMAP_DSS_OVL_CAP_GLOBAL_ALPHA)
			vout->win.global_alpha = win->global_alpha;
		else
			win->global_alpha = 0;
		if (vout->fbuf.flags & (V4L2_FBUF_FLAG_CHROMAKEY |
					V4L2_FBUF_FLAG_SRC_CHROMAKEY))
			enable = 1;
		else
			enable = 0;
		if (vout->fbuf.flags & V4L2_FBUF_FLAG_SRC_CHROMAKEY)
			key_type = OMAP_DSS_COLOR_KEY_VID_SRC;

		if (ovl->manager && ovl->manager->get_manager_info &&
		    ovl->manager->set_manager_info) {
			struct omap_overlay_manager_info info;

			ovl->manager->get_manager_info(ovl->manager, &info);
			info.trans_enabled = enable;
			info.trans_key_type = key_type;
			info.trans_key = vout->win.chromakey;

			if (ovl->manager->set_manager_info(ovl->manager, &info))
				return -EINVAL;
		}
	}
	return ret;
}