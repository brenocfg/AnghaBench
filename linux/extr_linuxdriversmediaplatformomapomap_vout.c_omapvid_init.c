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
struct TYPE_5__ {int width; int height; int left; int top; } ;
struct v4l2_window {TYPE_2__ w; } ;
struct omapvideo_info {int num_overlays; struct omap_overlay** overlays; } ;
struct omap_vout_device {int rotation; TYPE_3__* vid_dev; struct v4l2_window win; struct omapvideo_info vid_info; } ;
struct omap_video_timings {int /*<<< orphan*/  x_res; int /*<<< orphan*/  y_res; } ;
struct omap_overlay {struct omap_dss_device* (* get_device ) (struct omap_overlay*) ;} ;
struct TYPE_4__ {struct omap_video_timings timings; } ;
struct omap_dss_device {TYPE_1__ panel; } ;
struct TYPE_6__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  dss_rotation_180_degree 130 
#define  dss_rotation_270_degree 129 
#define  dss_rotation_90_degree 128 
 int omapvid_setup_overlay (struct omap_vout_device*,struct omap_overlay*,int,int,int,int,int /*<<< orphan*/ ) ; 
 struct omap_dss_device* stub1 (struct omap_overlay*) ; 
 int /*<<< orphan*/  swap (int,int) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int omapvid_init(struct omap_vout_device *vout, u32 addr)
{
	int ret = 0, i;
	struct v4l2_window *win;
	struct omap_overlay *ovl;
	int posx, posy, outw, outh;
	struct omap_video_timings *timing;
	struct omapvideo_info *ovid = &vout->vid_info;

	win = &vout->win;
	for (i = 0; i < ovid->num_overlays; i++) {
		struct omap_dss_device *dssdev;

		ovl = ovid->overlays[i];
		dssdev = ovl->get_device(ovl);

		if (!dssdev)
			return -EINVAL;

		timing = &dssdev->panel.timings;

		outw = win->w.width;
		outh = win->w.height;
		switch (vout->rotation) {
		case dss_rotation_90_degree:
			/* Invert the height and width for 90
			 * and 270 degree rotation
			 */
			swap(outw, outh);
			posy = (timing->y_res - win->w.width) - win->w.left;
			posx = win->w.top;
			break;

		case dss_rotation_180_degree:
			posx = (timing->x_res - win->w.width) - win->w.left;
			posy = (timing->y_res - win->w.height) - win->w.top;
			break;

		case dss_rotation_270_degree:
			swap(outw, outh);
			posy = win->w.left;
			posx = (timing->x_res - win->w.height) - win->w.top;
			break;

		default:
			posx = win->w.left;
			posy = win->w.top;
			break;
		}

		ret = omapvid_setup_overlay(vout, ovl, posx, posy,
				outw, outh, addr);
		if (ret)
			goto omapvid_init_err;
	}
	return 0;

omapvid_init_err:
	v4l2_warn(&vout->vid_dev->v4l2_dev, "apply_changes failed\n");
	return ret;
}