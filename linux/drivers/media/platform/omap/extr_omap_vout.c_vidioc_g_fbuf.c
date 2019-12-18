#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int height; int width; int bytesperline; int sizeimage; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;
struct v4l2_framebuffer {int flags; int /*<<< orphan*/  capability; int /*<<< orphan*/  base; TYPE_3__ fmt; } ;
struct omapvideo_info {struct omap_overlay** overlays; } ;
struct TYPE_7__ {int height; int width; } ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  capability; int /*<<< orphan*/  base; TYPE_2__ fmt; } ;
struct omap_vout_device {TYPE_4__ fbuf; struct omapvideo_info vid_info; } ;
struct omap_video_timings {int y_res; int x_res; } ;
struct omap_overlay_manager_info {scalar_t__ trans_key_type; scalar_t__ partial_alpha_enabled; } ;
struct omap_overlay {TYPE_5__* manager; struct omap_dss_device* (* get_device ) (struct omap_overlay*) ;} ;
struct TYPE_6__ {struct omap_video_timings timings; } ;
struct omap_dss_device {TYPE_1__ panel; } ;
struct file {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* get_manager_info ) (TYPE_5__*,struct omap_overlay_manager_info*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OMAP_DSS_COLOR_KEY_GFX_DST ; 
 scalar_t__ OMAP_DSS_COLOR_KEY_VID_SRC ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int V4L2_FBUF_FLAG_CHROMAKEY ; 
 int V4L2_FBUF_FLAG_LOCAL_ALPHA ; 
 int V4L2_FBUF_FLAG_SRC_CHROMAKEY ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_RGBA32 ; 
 struct omap_dss_device* stub1 (struct omap_overlay*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,struct omap_overlay_manager_info*) ; 
 struct omap_vout_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_fbuf(struct file *file, void *fh,
		struct v4l2_framebuffer *a)
{
	struct omap_overlay *ovl;
	struct omapvideo_info *ovid;
	struct omap_vout_device *vout = video_drvdata(file);
	struct omap_overlay_manager_info info;
	struct omap_video_timings *timing;
	struct omap_dss_device *dssdev;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];
	/* get the display device attached to the overlay */
	dssdev = ovl->get_device(ovl);

	if (!dssdev)
		return -EINVAL;

	timing = &dssdev->panel.timings;

	vout->fbuf.fmt.height = timing->y_res;
	vout->fbuf.fmt.width = timing->x_res;
	a->fmt.field = V4L2_FIELD_NONE;
	a->fmt.colorspace = V4L2_COLORSPACE_SRGB;
	a->fmt.pixelformat = V4L2_PIX_FMT_RGBA32;
	a->fmt.height = vout->fbuf.fmt.height;
	a->fmt.width = vout->fbuf.fmt.width;
	a->fmt.bytesperline = vout->fbuf.fmt.width * 4;
	a->fmt.sizeimage = a->fmt.height * a->fmt.bytesperline;
	a->base = vout->fbuf.base;

	a->flags = vout->fbuf.flags;
	a->capability = vout->fbuf.capability;
	a->flags &= ~(V4L2_FBUF_FLAG_SRC_CHROMAKEY | V4L2_FBUF_FLAG_CHROMAKEY |
		      V4L2_FBUF_FLAG_LOCAL_ALPHA);

	if (ovl->manager && ovl->manager->get_manager_info) {
		ovl->manager->get_manager_info(ovl->manager, &info);
		if (info.trans_key_type == OMAP_DSS_COLOR_KEY_VID_SRC)
			a->flags |= V4L2_FBUF_FLAG_SRC_CHROMAKEY;
		if (info.trans_key_type == OMAP_DSS_COLOR_KEY_GFX_DST)
			a->flags |= V4L2_FBUF_FLAG_CHROMAKEY;
		if (info.partial_alpha_enabled)
			a->flags |= V4L2_FBUF_FLAG_LOCAL_ALPHA;
	}

	return 0;
}