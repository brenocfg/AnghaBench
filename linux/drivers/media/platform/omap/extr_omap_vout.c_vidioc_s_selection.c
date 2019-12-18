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
struct v4l2_selection {scalar_t__ type; scalar_t__ target; int /*<<< orphan*/  r; } ;
struct omapvideo_info {struct omap_overlay** overlays; } ;
struct TYPE_5__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct omap_vout_device {TYPE_3__ fbuf; int /*<<< orphan*/  win; int /*<<< orphan*/  crop; int /*<<< orphan*/  pix; struct omapvideo_info vid_info; int /*<<< orphan*/  vq; } ;
struct omap_video_timings {int /*<<< orphan*/  x_res; int /*<<< orphan*/  y_res; } ;
struct omap_overlay {struct omap_dss_device* (* get_device ) (struct omap_overlay*) ;} ;
struct TYPE_4__ {struct omap_video_timings timings; } ;
struct omap_dss_device {TYPE_1__ panel; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 scalar_t__ is_rotation_90_or_270 (struct omap_vout_device*) ; 
 int omap_vout_new_crop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 struct omap_dss_device* stub1 (struct omap_overlay*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct omap_vout_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_selection(struct file *file, void *fh, struct v4l2_selection *sel)
{
	int ret = -EINVAL;
	struct omap_vout_device *vout = video_drvdata(file);
	struct omapvideo_info *ovid;
	struct omap_overlay *ovl;
	struct omap_video_timings *timing;
	struct omap_dss_device *dssdev;

	if (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;

	if (sel->target != V4L2_SEL_TGT_CROP)
		return -EINVAL;

	if (vb2_is_busy(&vout->vq))
		return -EBUSY;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];
	/* get the display device attached to the overlay */
	dssdev = ovl->get_device(ovl);

	if (!dssdev) {
		ret = -EINVAL;
		goto s_crop_err;
	}

	timing = &dssdev->panel.timings;

	if (is_rotation_90_or_270(vout)) {
		vout->fbuf.fmt.height = timing->x_res;
		vout->fbuf.fmt.width = timing->y_res;
	} else {
		vout->fbuf.fmt.height = timing->y_res;
		vout->fbuf.fmt.width = timing->x_res;
	}

	ret = omap_vout_new_crop(&vout->pix, &vout->crop, &vout->win,
				 &vout->fbuf, &sel->r);

s_crop_err:
	return ret;
}