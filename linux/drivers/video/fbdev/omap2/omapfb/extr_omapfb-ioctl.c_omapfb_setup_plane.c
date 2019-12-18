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
struct omapfb_plane_info {scalar_t__ enabled; int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; int /*<<< orphan*/  pos_y; int /*<<< orphan*/  pos_x; int /*<<< orphan*/  mem_idx; } ;
struct omapfb_info {scalar_t__ num_overlays; struct omapfb2_mem_region* region; struct omap_overlay** overlays; struct omapfb2_device* fbdev; } ;
struct omapfb2_mem_region {scalar_t__ id; int /*<<< orphan*/  size; } ;
struct omapfb2_device {int /*<<< orphan*/  dev; } ;
struct omap_overlay_info {int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; int /*<<< orphan*/  pos_y; int /*<<< orphan*/  pos_x; } ;
struct omap_overlay {int (* disable ) (struct omap_overlay*) ;int (* set_overlay_info ) (struct omap_overlay*,struct omap_overlay_info*) ;int (* enable ) (struct omap_overlay*) ;TYPE_1__* manager; int /*<<< orphan*/  (* get_overlay_info ) (struct omap_overlay*,struct omap_overlay_info*) ;} ;
struct fb_info {int dummy; } ;
struct TYPE_2__ {int (* apply ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int EINVAL ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct omapfb2_mem_region* get_mem_region (struct omapfb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_get_mem_region (struct omapfb2_mem_region*) ; 
 int /*<<< orphan*/  omapfb_put_mem_region (struct omapfb2_mem_region*) ; 
 int omapfb_setup_overlay (struct fb_info*,struct omap_overlay*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fb_fix (struct fb_info*) ; 
 int /*<<< orphan*/  stub1 (struct omap_overlay*,struct omap_overlay_info*) ; 
 int stub2 (struct omap_overlay*) ; 
 int /*<<< orphan*/  stub3 (struct omap_overlay*,struct omap_overlay_info*) ; 
 int stub4 (struct omap_overlay*,struct omap_overlay_info*) ; 
 int stub5 (TYPE_1__*) ; 
 int stub6 (struct omap_overlay*) ; 
 int stub7 (struct omap_overlay*,struct omap_overlay_info*) ; 

__attribute__((used)) static int omapfb_setup_plane(struct fb_info *fbi, struct omapfb_plane_info *pi)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct omapfb2_device *fbdev = ofbi->fbdev;
	struct omap_overlay *ovl;
	struct omap_overlay_info old_info;
	struct omapfb2_mem_region *old_rg, *new_rg;
	int r = 0;

	DBG("omapfb_setup_plane\n");

	if (ofbi->num_overlays == 0) {
		r = -EINVAL;
		goto out;
	}

	/* XXX uses only the first overlay */
	ovl = ofbi->overlays[0];

	old_rg = ofbi->region;
	new_rg = get_mem_region(ofbi, pi->mem_idx);
	if (!new_rg) {
		r = -EINVAL;
		goto out;
	}

	/* Take the locks in a specific order to keep lockdep happy */
	if (old_rg->id < new_rg->id) {
		omapfb_get_mem_region(old_rg);
		omapfb_get_mem_region(new_rg);
	} else if (new_rg->id < old_rg->id) {
		omapfb_get_mem_region(new_rg);
		omapfb_get_mem_region(old_rg);
	} else
		omapfb_get_mem_region(old_rg);

	if (pi->enabled && !new_rg->size) {
		/*
		 * This plane's memory was freed, can't enable it
		 * until it's reallocated.
		 */
		r = -EINVAL;
		goto put_mem;
	}

	ovl->get_overlay_info(ovl, &old_info);

	if (old_rg != new_rg) {
		ofbi->region = new_rg;
		set_fb_fix(fbi);
	}

	if (!pi->enabled) {
		r = ovl->disable(ovl);
		if (r)
			goto undo;
	}

	if (pi->enabled) {
		r = omapfb_setup_overlay(fbi, ovl, pi->pos_x, pi->pos_y,
			pi->out_width, pi->out_height);
		if (r)
			goto undo;
	} else {
		struct omap_overlay_info info;

		ovl->get_overlay_info(ovl, &info);

		info.pos_x = pi->pos_x;
		info.pos_y = pi->pos_y;
		info.out_width = pi->out_width;
		info.out_height = pi->out_height;

		r = ovl->set_overlay_info(ovl, &info);
		if (r)
			goto undo;
	}

	if (ovl->manager) {
		r = ovl->manager->apply(ovl->manager);
		if (r)
			goto undo;
	}

	if (pi->enabled) {
		r = ovl->enable(ovl);
		if (r)
			goto undo;
	}

	/* Release the locks in a specific order to keep lockdep happy */
	if (old_rg->id > new_rg->id) {
		omapfb_put_mem_region(old_rg);
		omapfb_put_mem_region(new_rg);
	} else if (new_rg->id > old_rg->id) {
		omapfb_put_mem_region(new_rg);
		omapfb_put_mem_region(old_rg);
	} else
		omapfb_put_mem_region(old_rg);

	return 0;

 undo:
	if (old_rg != new_rg) {
		ofbi->region = old_rg;
		set_fb_fix(fbi);
	}

	ovl->set_overlay_info(ovl, &old_info);
 put_mem:
	/* Release the locks in a specific order to keep lockdep happy */
	if (old_rg->id > new_rg->id) {
		omapfb_put_mem_region(old_rg);
		omapfb_put_mem_region(new_rg);
	} else if (new_rg->id > old_rg->id) {
		omapfb_put_mem_region(new_rg);
		omapfb_put_mem_region(old_rg);
	} else
		omapfb_put_mem_region(old_rg);
 out:
	dev_err(fbdev->dev, "setup_plane failed\n");

	return r;
}