#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_4__ fmt; } ;
struct omapvideo_info {struct omap_overlay** overlays; } ;
struct TYPE_6__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct TYPE_7__ {TYPE_2__ fmt; } ;
struct omap_vout_device {TYPE_3__ fbuf; struct omapvideo_info vid_info; } ;
struct omap_video_timings {int /*<<< orphan*/  x_res; int /*<<< orphan*/  y_res; } ;
struct omap_overlay {struct omap_dss_device* (* get_device ) (struct omap_overlay*) ;} ;
struct TYPE_5__ {struct omap_video_timings timings; } ;
struct omap_dss_device {TYPE_1__ panel; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  omap_vout_try_format (int /*<<< orphan*/ *) ; 
 struct omap_dss_device* stub1 (struct omap_overlay*) ; 
 struct omap_vout_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_out(struct file *file, void *fh,
			struct v4l2_format *f)
{
	struct omap_overlay *ovl;
	struct omapvideo_info *ovid;
	struct omap_video_timings *timing;
	struct omap_vout_device *vout = video_drvdata(file);
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

	omap_vout_try_format(&f->fmt.pix);
	return 0;
}