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
struct omap_dss_device {TYPE_1__* ops; } ;
struct omap_connector {struct omap_dss_device* output; struct omap_dss_device* hpd; } ;
struct drm_connector {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unregister_hpd_cb ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct omap_connector*) ; 
 int /*<<< orphan*/  omapdss_device_put (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 
 struct omap_connector* to_omap_connector (struct drm_connector*) ; 

__attribute__((used)) static void omap_connector_destroy(struct drm_connector *connector)
{
	struct omap_connector *omap_connector = to_omap_connector(connector);

	DBG("%s", connector->name);

	if (omap_connector->hpd) {
		struct omap_dss_device *hpd = omap_connector->hpd;

		hpd->ops->unregister_hpd_cb(hpd);
		omapdss_device_put(hpd);
		omap_connector->hpd = NULL;
	}

	drm_connector_unregister(connector);
	drm_connector_cleanup(connector);

	omapdss_device_put(omap_connector->output);

	kfree(omap_connector);
}