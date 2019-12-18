#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omapfb2_device {int num_displays; int num_overlays; int /*<<< orphan*/  dev; struct omap_overlay** overlays; TYPE_1__* displays; } ;
struct omap_overlay_manager {int /*<<< orphan*/  name; } ;
struct omap_overlay {int (* set_manager ) (struct omap_overlay*,struct omap_overlay_manager*) ;int /*<<< orphan*/  name; int /*<<< orphan*/  (* unset_manager ) (struct omap_overlay*) ;scalar_t__ manager; } ;
struct omap_dss_device {TYPE_2__* driver; } ;
struct TYPE_4__ {int (* connect ) (struct omap_dss_device*) ;} ;
struct TYPE_3__ {struct omap_dss_device* dssdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap_overlay_manager* omapdss_find_mgr_from_display (struct omap_dss_device*) ; 
 int stub1 (struct omap_dss_device*) ; 
 int stub2 (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub3 (struct omap_overlay*) ; 
 int stub4 (struct omap_overlay*,struct omap_overlay_manager*) ; 

__attribute__((used)) static int omapfb_init_connections(struct omapfb2_device *fbdev,
		struct omap_dss_device *def_dssdev)
{
	int i, r;
	struct omap_overlay_manager *mgr;

	r = def_dssdev->driver->connect(def_dssdev);
	if (r) {
		dev_err(fbdev->dev, "failed to connect default display\n");
		return r;
	}

	for (i = 0; i < fbdev->num_displays; ++i) {
		struct omap_dss_device *dssdev = fbdev->displays[i].dssdev;

		if (dssdev == def_dssdev)
			continue;

		/*
		 * We don't care if the connect succeeds or not. We just want to
		 * connect as many displays as possible.
		 */
		dssdev->driver->connect(dssdev);
	}

	mgr = omapdss_find_mgr_from_display(def_dssdev);

	if (!mgr) {
		dev_err(fbdev->dev, "no ovl manager for the default display\n");
		return -EINVAL;
	}

	for (i = 0; i < fbdev->num_overlays; i++) {
		struct omap_overlay *ovl = fbdev->overlays[i];

		if (ovl->manager)
			ovl->unset_manager(ovl);

		r = ovl->set_manager(ovl, mgr);
		if (r)
			dev_warn(fbdev->dev,
					"failed to connect overlay %s to manager %s\n",
					ovl->name, mgr->name);
	}

	return 0;
}