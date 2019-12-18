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
struct omap_overlay_manager {size_t id; } ;
struct fb_info {int dummy; } ;
struct TYPE_2__ {struct omap_overlay_manager* manager; } ;

/* Variables and functions */
 int EINVAL ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 struct omapfb_color_key* omapfb_color_keys ; 
 int /*<<< orphan*/  omapfb_lock (struct omapfb2_device*) ; 
 int /*<<< orphan*/  omapfb_unlock (struct omapfb2_device*) ; 

__attribute__((used)) static int omapfb_get_color_key(struct fb_info *fbi,
		struct omapfb_color_key *ck)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct omapfb2_device *fbdev = ofbi->fbdev;
	struct omap_overlay_manager *mgr = NULL;
	int r = 0;
	int i;

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

	*ck = omapfb_color_keys[mgr->id];
err:
	omapfb_unlock(fbdev);

	return r;
}