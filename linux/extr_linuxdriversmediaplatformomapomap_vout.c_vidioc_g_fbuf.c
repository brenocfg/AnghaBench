#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_framebuffer {int capability; int /*<<< orphan*/  flags; } ;
struct omapvideo_info {struct omap_overlay** overlays; } ;
struct omap_vout_device {struct omapvideo_info vid_info; } ;
struct omap_overlay_manager_info {scalar_t__ trans_key_type; scalar_t__ partial_alpha_enabled; } ;
struct omap_overlay {TYPE_1__* manager; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_manager_info ) (TYPE_1__*,struct omap_overlay_manager_info*) ;} ;

/* Variables and functions */
 scalar_t__ OMAP_DSS_COLOR_KEY_GFX_DST ; 
 scalar_t__ OMAP_DSS_COLOR_KEY_VID_SRC ; 
 int V4L2_FBUF_CAP_CHROMAKEY ; 
 int V4L2_FBUF_CAP_LOCAL_ALPHA ; 
 int V4L2_FBUF_CAP_SRC_CHROMAKEY ; 
 int /*<<< orphan*/  V4L2_FBUF_FLAG_CHROMAKEY ; 
 int /*<<< orphan*/  V4L2_FBUF_FLAG_LOCAL_ALPHA ; 
 int /*<<< orphan*/  V4L2_FBUF_FLAG_OVERLAY ; 
 int /*<<< orphan*/  V4L2_FBUF_FLAG_SRC_CHROMAKEY ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct omap_overlay_manager_info*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,struct omap_overlay_manager_info*) ; 

__attribute__((used)) static int vidioc_g_fbuf(struct file *file, void *fh,
		struct v4l2_framebuffer *a)
{
	struct omap_overlay *ovl;
	struct omapvideo_info *ovid;
	struct omap_vout_device *vout = fh;
	struct omap_overlay_manager_info info;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];

	/* The video overlay must stay within the framebuffer and can't be
	   positioned independently. */
	a->flags = V4L2_FBUF_FLAG_OVERLAY;
	a->capability = V4L2_FBUF_CAP_LOCAL_ALPHA | V4L2_FBUF_CAP_CHROMAKEY
		| V4L2_FBUF_CAP_SRC_CHROMAKEY;

	if (ovl->manager && ovl->manager->get_manager_info) {
		ovl->manager->get_manager_info(ovl->manager, &info);
		if (info.trans_key_type == OMAP_DSS_COLOR_KEY_VID_SRC)
			a->flags |= V4L2_FBUF_FLAG_SRC_CHROMAKEY;
		if (info.trans_key_type == OMAP_DSS_COLOR_KEY_GFX_DST)
			a->flags |= V4L2_FBUF_FLAG_CHROMAKEY;
	}
	if (ovl->manager && ovl->manager->get_manager_info) {
		ovl->manager->get_manager_info(ovl->manager, &info);
		if (info.partial_alpha_enabled)
			a->flags |= V4L2_FBUF_FLAG_LOCAL_ALPHA;
	}

	return 0;
}