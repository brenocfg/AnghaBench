#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_window {int /*<<< orphan*/  chromakey; int /*<<< orphan*/  global_alpha; int /*<<< orphan*/  field; int /*<<< orphan*/  w; } ;
struct TYPE_4__ {struct v4l2_window win; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct omapvideo_info {struct omap_overlay** overlays; } ;
struct TYPE_5__ {int /*<<< orphan*/  global_alpha; int /*<<< orphan*/  field; int /*<<< orphan*/  w; } ;
struct omap_vout_device {TYPE_2__ win; struct omapvideo_info vid_info; } ;
struct omap_overlay_manager_info {int /*<<< orphan*/  trans_key; } ;
struct omap_overlay {TYPE_3__* manager; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_manager_info ) (TYPE_3__*,struct omap_overlay_manager_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct omap_overlay_manager_info*) ; 

__attribute__((used)) static int vidioc_g_fmt_vid_overlay(struct file *file, void *fh,
			struct v4l2_format *f)
{
	u32 key_value =  0;
	struct omap_overlay *ovl;
	struct omapvideo_info *ovid;
	struct omap_vout_device *vout = fh;
	struct omap_overlay_manager_info info;
	struct v4l2_window *win = &f->fmt.win;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];

	win->w = vout->win.w;
	win->field = vout->win.field;
	win->global_alpha = vout->win.global_alpha;

	if (ovl->manager && ovl->manager->get_manager_info) {
		ovl->manager->get_manager_info(ovl->manager, &info);
		key_value = info.trans_key;
	}
	win->chromakey = key_value;
	return 0;
}