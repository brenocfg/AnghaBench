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
struct omapfb_info {int id; int num_overlays; struct omap_overlay** overlays; TYPE_2__* region; int /*<<< orphan*/  mirror; int /*<<< orphan*/  rotation_type; struct omapfb2_device* fbdev; } ;
struct omapfb2_device {int num_fbs; int /*<<< orphan*/  dev; struct fb_info** fbs; struct omap_overlay** overlays; int /*<<< orphan*/  num_overlays; TYPE_2__* regions; } ;
struct omap_overlay {TYPE_1__* manager; } ;
struct fb_info {int dummy; } ;
struct TYPE_5__ {int id; scalar_t__ size; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* apply ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int CONFIG_FB_OMAP2_NUM_FBS ; 
 int /*<<< orphan*/  DBG (char*,...) ; 
 int ENOMEM ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int /*<<< orphan*/  OMAP_DSS_ROT_DMA ; 
 int /*<<< orphan*/  OMAP_DSS_ROT_VRFB ; 
 int /*<<< orphan*/  clear_fb_info (struct fb_info*) ; 
 int /*<<< orphan*/  def_mirror ; 
 scalar_t__ def_vrfb ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct fb_info* framebuffer_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int omapfb_allocate_all_fbs (struct omapfb2_device*) ; 
 int omapfb_apply_changes (struct fb_info*,int) ; 
 int /*<<< orphan*/  omapfb_clear_fb (struct fb_info*) ; 
 int omapfb_fb_init (struct omapfb2_device*,struct fb_info*) ; 
 int /*<<< orphan*/  omapfb_get_mem_region (TYPE_2__*) ; 
 int omapfb_overlay_enable (struct omap_overlay*,int) ; 
 int /*<<< orphan*/  omapfb_put_mem_region (TYPE_2__*) ; 
 int register_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static int omapfb_create_framebuffers(struct omapfb2_device *fbdev)
{
	int r, i;

	fbdev->num_fbs = 0;

	DBG("create %d framebuffers\n",	CONFIG_FB_OMAP2_NUM_FBS);

	/* allocate fb_infos */
	for (i = 0; i < CONFIG_FB_OMAP2_NUM_FBS; i++) {
		struct fb_info *fbi;
		struct omapfb_info *ofbi;

		fbi = framebuffer_alloc(sizeof(struct omapfb_info),
				fbdev->dev);
		if (!fbi)
			return -ENOMEM;

		clear_fb_info(fbi);

		fbdev->fbs[i] = fbi;

		ofbi = FB2OFB(fbi);
		ofbi->fbdev = fbdev;
		ofbi->id = i;

		ofbi->region = &fbdev->regions[i];
		ofbi->region->id = i;
		init_rwsem(&ofbi->region->lock);

		/* assign these early, so that fb alloc can use them */
		ofbi->rotation_type = def_vrfb ? OMAP_DSS_ROT_VRFB :
			OMAP_DSS_ROT_DMA;
		ofbi->mirror = def_mirror;

		fbdev->num_fbs++;
	}

	DBG("fb_infos allocated\n");

	/* assign overlays for the fbs */
	for (i = 0; i < min(fbdev->num_fbs, fbdev->num_overlays); i++) {
		struct omapfb_info *ofbi = FB2OFB(fbdev->fbs[i]);

		ofbi->overlays[0] = fbdev->overlays[i];
		ofbi->num_overlays = 1;
	}

	/* allocate fb memories */
	r = omapfb_allocate_all_fbs(fbdev);
	if (r) {
		dev_err(fbdev->dev, "failed to allocate fbmem\n");
		return r;
	}

	DBG("fbmems allocated\n");

	/* setup fb_infos */
	for (i = 0; i < fbdev->num_fbs; i++) {
		struct fb_info *fbi = fbdev->fbs[i];
		struct omapfb_info *ofbi = FB2OFB(fbi);

		omapfb_get_mem_region(ofbi->region);
		r = omapfb_fb_init(fbdev, fbi);
		omapfb_put_mem_region(ofbi->region);

		if (r) {
			dev_err(fbdev->dev, "failed to setup fb_info\n");
			return r;
		}
	}

	for (i = 0; i < fbdev->num_fbs; i++) {
		struct fb_info *fbi = fbdev->fbs[i];
		struct omapfb_info *ofbi = FB2OFB(fbi);

		if (ofbi->region->size == 0)
			continue;

		omapfb_clear_fb(fbi);
	}

	DBG("fb_infos initialized\n");

	for (i = 0; i < fbdev->num_fbs; i++) {
		r = register_framebuffer(fbdev->fbs[i]);
		if (r != 0) {
			dev_err(fbdev->dev,
				"registering framebuffer %d failed\n", i);
			return r;
		}
	}

	DBG("framebuffers registered\n");

	for (i = 0; i < fbdev->num_fbs; i++) {
		struct fb_info *fbi = fbdev->fbs[i];
		struct omapfb_info *ofbi = FB2OFB(fbi);

		omapfb_get_mem_region(ofbi->region);
		r = omapfb_apply_changes(fbi, 1);
		omapfb_put_mem_region(ofbi->region);

		if (r) {
			dev_err(fbdev->dev, "failed to change mode\n");
			return r;
		}
	}

	/* Enable fb0 */
	if (fbdev->num_fbs > 0) {
		struct omapfb_info *ofbi = FB2OFB(fbdev->fbs[0]);

		if (ofbi->num_overlays > 0) {
			struct omap_overlay *ovl = ofbi->overlays[0];

			ovl->manager->apply(ovl->manager);

			r = omapfb_overlay_enable(ovl, 1);

			if (r) {
				dev_err(fbdev->dev,
						"failed to enable overlay\n");
				return r;
			}
		}
	}

	DBG("create_framebuffers done\n");

	return 0;
}