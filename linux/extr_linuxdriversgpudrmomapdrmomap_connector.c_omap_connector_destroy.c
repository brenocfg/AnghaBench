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
struct omap_dss_device {TYPE_1__* driver; int /*<<< orphan*/  name; } ;
struct omap_connector {struct omap_dss_device* dssdev; } ;
struct drm_connector {scalar_t__ polled; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unregister_hpd_cb ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct omap_connector*) ; 
 int /*<<< orphan*/  omap_dss_put_device (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 
 struct omap_connector* to_omap_connector (struct drm_connector*) ; 

__attribute__((used)) static void omap_connector_destroy(struct drm_connector *connector)
{
	struct omap_connector *omap_connector = to_omap_connector(connector);
	struct omap_dss_device *dssdev = omap_connector->dssdev;

	DBG("%s", omap_connector->dssdev->name);
	if (connector->polled == DRM_CONNECTOR_POLL_HPD &&
	    dssdev->driver->unregister_hpd_cb) {
		dssdev->driver->unregister_hpd_cb(dssdev);
	}
	drm_connector_unregister(connector);
	drm_connector_cleanup(connector);
	kfree(omap_connector);

	omap_dss_put_device(dssdev);
}