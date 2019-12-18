#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct omapfb_info {struct omapfb2_device* fbdev; } ;
struct omapfb_display_data {int update_mode; } ;
struct omapfb2_device {int dummy; } ;
struct omap_dss_device {int caps; } ;
struct fb_info {int dummy; } ;
typedef  enum omapfb_update_mode { ____Placeholder_omapfb_update_mode } omapfb_update_mode ;

/* Variables and functions */
 int EINVAL ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int OMAPFB_AUTO_UPDATE ; 
 int OMAPFB_MANUAL_UPDATE ; 
 int OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE ; 
 struct omap_dss_device* fb2display (struct fb_info*) ; 
 struct omapfb_display_data* get_display_data (struct omapfb2_device*,struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapfb_lock (struct omapfb2_device*) ; 
 int /*<<< orphan*/  omapfb_start_auto_update (struct omapfb2_device*,struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapfb_stop_auto_update (struct omapfb2_device*,struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapfb_unlock (struct omapfb2_device*) ; 

int omapfb_set_update_mode(struct fb_info *fbi,
				   enum omapfb_update_mode mode)
{
	struct omap_dss_device *display = fb2display(fbi);
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct omapfb2_device *fbdev = ofbi->fbdev;
	struct omapfb_display_data *d;
	int r;

	if (!display)
		return -EINVAL;

	if (mode != OMAPFB_AUTO_UPDATE && mode != OMAPFB_MANUAL_UPDATE)
		return -EINVAL;

	omapfb_lock(fbdev);

	d = get_display_data(fbdev, display);

	if (d->update_mode == mode) {
		omapfb_unlock(fbdev);
		return 0;
	}

	r = 0;

	if (display->caps & OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE) {
		if (mode == OMAPFB_AUTO_UPDATE)
			omapfb_start_auto_update(fbdev, display);
		else /* MANUAL_UPDATE */
			omapfb_stop_auto_update(fbdev, display);

		d->update_mode = mode;
	} else { /* AUTO_UPDATE */
		if (mode == OMAPFB_MANUAL_UPDATE)
			r = -EINVAL;
	}

	omapfb_unlock(fbdev);

	return r;
}