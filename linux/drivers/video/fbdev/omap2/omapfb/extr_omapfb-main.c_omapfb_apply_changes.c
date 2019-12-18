#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct omapfb_info {int num_overlays; int* rotation; TYPE_1__* region; int /*<<< orphan*/  id; struct omap_overlay** overlays; } ;
struct omap_overlay_info {scalar_t__ pos_y; scalar_t__ pos_x; scalar_t__ out_height; scalar_t__ out_width; } ;
struct omap_overlay {int caps; TYPE_2__* manager; int /*<<< orphan*/  (* get_overlay_info ) (struct omap_overlay*,struct omap_overlay_info*) ;int /*<<< orphan*/  id; } ;
struct fb_var_screeninfo {int rotate; scalar_t__ yres; scalar_t__ xres; } ;
struct fb_info {struct fb_var_screeninfo var; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* apply ) (TYPE_2__*) ;} ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/  lock_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int FB_ROTATE_CCW ; 
 int FB_ROTATE_CW ; 
 int OMAP_DSS_OVL_CAP_SCALE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_fb (struct fb_info*) ; 
 int /*<<< orphan*/  omapfb_overlay_enable (struct omap_overlay*,int /*<<< orphan*/ ) ; 
 int omapfb_setup_overlay (struct fb_info*,struct omap_overlay*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ omapfb_test_pattern ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (struct omap_overlay*,struct omap_overlay_info*) ; 
 int /*<<< orphan*/  stub3 (struct omap_overlay*,struct omap_overlay_info*) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*) ; 

int omapfb_apply_changes(struct fb_info *fbi, int init)
{
	int r = 0;
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct fb_var_screeninfo *var = &fbi->var;
	struct omap_overlay *ovl;
	u16 posx, posy;
	u16 outw, outh;
	int i;

#ifdef DEBUG
	if (omapfb_test_pattern)
		fill_fb(fbi);
#endif

	WARN_ON(!atomic_read(&ofbi->region->lock_count));

	for (i = 0; i < ofbi->num_overlays; i++) {
		ovl = ofbi->overlays[i];

		DBG("apply_changes, fb %d, ovl %d\n", ofbi->id, ovl->id);

		if (ofbi->region->size == 0) {
			/* the fb is not available. disable the overlay */
			omapfb_overlay_enable(ovl, 0);
			if (!init && ovl->manager)
				ovl->manager->apply(ovl->manager);
			continue;
		}

		if (init || (ovl->caps & OMAP_DSS_OVL_CAP_SCALE) == 0) {
			int rotation = (var->rotate + ofbi->rotation[i]) % 4;
			if (rotation == FB_ROTATE_CW ||
					rotation == FB_ROTATE_CCW) {
				outw = var->yres;
				outh = var->xres;
			} else {
				outw = var->xres;
				outh = var->yres;
			}
		} else {
			struct omap_overlay_info info;
			ovl->get_overlay_info(ovl, &info);
			outw = info.out_width;
			outh = info.out_height;
		}

		if (init) {
			posx = 0;
			posy = 0;
		} else {
			struct omap_overlay_info info;
			ovl->get_overlay_info(ovl, &info);
			posx = info.pos_x;
			posy = info.pos_y;
		}

		r = omapfb_setup_overlay(fbi, ovl, posx, posy, outw, outh);
		if (r)
			goto err;

		if (!init && ovl->manager)
			ovl->manager->apply(ovl->manager);
	}
	return 0;
err:
	DBG("apply_changes failed\n");
	return r;
}