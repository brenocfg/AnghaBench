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
struct omapfb2_device {int num_overlays; int num_fbs; int num_displays; int /*<<< orphan*/  dev; int /*<<< orphan*/ * auto_update_wq; TYPE_1__* displays; int /*<<< orphan*/ * fbs; struct omap_overlay** overlays; } ;
struct omap_overlay {int /*<<< orphan*/  (* unset_manager ) (struct omap_overlay*) ;scalar_t__ manager; int /*<<< orphan*/  (* disable ) (struct omap_overlay*) ;} ;
struct omap_dss_device {scalar_t__ state; TYPE_2__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disconnect ) (struct omap_dss_device*) ;int /*<<< orphan*/  (* disable ) (struct omap_dss_device*) ;} ;
struct TYPE_3__ {scalar_t__ auto_update_work_enabled; struct omap_dss_device* dssdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 scalar_t__ OMAP_DSS_DISPLAY_DISABLED ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fbinfo_cleanup (struct omapfb2_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dss_put_device (struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapfb_free_all_fbmem (struct omapfb2_device*) ; 
 int /*<<< orphan*/  omapfb_stop_auto_update (struct omapfb2_device*,struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub1 (struct omap_overlay*) ; 
 int /*<<< orphan*/  stub2 (struct omap_overlay*) ; 
 int /*<<< orphan*/  stub3 (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub4 (struct omap_dss_device*) ; 
 int /*<<< orphan*/  unregister_framebuffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omapfb_free_resources(struct omapfb2_device *fbdev)
{
	int i;

	DBG("free_resources\n");

	if (fbdev == NULL)
		return;

	for (i = 0; i < fbdev->num_overlays; i++) {
		struct omap_overlay *ovl = fbdev->overlays[i];

		ovl->disable(ovl);

		if (ovl->manager)
			ovl->unset_manager(ovl);
	}

	for (i = 0; i < fbdev->num_fbs; i++)
		unregister_framebuffer(fbdev->fbs[i]);

	/* free the reserved fbmem */
	omapfb_free_all_fbmem(fbdev);

	for (i = 0; i < fbdev->num_fbs; i++) {
		fbinfo_cleanup(fbdev, fbdev->fbs[i]);
		framebuffer_release(fbdev->fbs[i]);
	}

	for (i = 0; i < fbdev->num_displays; i++) {
		struct omap_dss_device *dssdev = fbdev->displays[i].dssdev;

		if (fbdev->displays[i].auto_update_work_enabled)
			omapfb_stop_auto_update(fbdev, dssdev);

		if (dssdev->state != OMAP_DSS_DISPLAY_DISABLED)
			dssdev->driver->disable(dssdev);

		dssdev->driver->disconnect(dssdev);

		omap_dss_put_device(dssdev);
	}

	if (fbdev->auto_update_wq != NULL) {
		flush_workqueue(fbdev->auto_update_wq);
		destroy_workqueue(fbdev->auto_update_wq);
		fbdev->auto_update_wq = NULL;
	}

	dev_set_drvdata(fbdev->dev, NULL);
}