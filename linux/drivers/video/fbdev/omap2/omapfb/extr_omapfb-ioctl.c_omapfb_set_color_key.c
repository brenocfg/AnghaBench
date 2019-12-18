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
struct omapfb_info {int num_overlays; TYPE_1__** overlays; struct omapfb2_device* fbdev; } ;
struct omapfb_color_key {int dummy; } ;
struct omapfb2_device {int dummy; } ;
struct omap_overlay_manager {int dummy; } ;
struct fb_info {int dummy; } ;
struct TYPE_2__ {struct omap_overlay_manager* manager; } ;

/* Variables and functions */
 int EINVAL ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int _omapfb_set_color_key (struct omap_overlay_manager*,struct omapfb_color_key*) ; 
 int /*<<< orphan*/  omapfb_lock (struct omapfb2_device*) ; 
 int /*<<< orphan*/  omapfb_unlock (struct omapfb2_device*) ; 

__attribute__((used)) static int omapfb_set_color_key(struct fb_info *fbi,
		struct omapfb_color_key *ck)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct omapfb2_device *fbdev = ofbi->fbdev;
	int r;
	int i;
	struct omap_overlay_manager *mgr = NULL;

	omapfb_lock(fbdev);

	for (i = 0; i < ofbi->num_overlays; i++) {
		if (ofbi->overlays[i]->manager) {
			mgr = ofbi->overlays[i]->manager;
			break;
		}
	}

	if (!mgr) {
		r = -EINVAL;
		goto err;
	}

	r = _omapfb_set_color_key(mgr, ck);
err:
	omapfb_unlock(fbdev);

	return r;
}