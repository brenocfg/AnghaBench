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
struct omap_connector {struct omap_dss_device* hpd; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unregister_hpd_cb ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 
 struct omap_connector* to_omap_connector (struct drm_connector*) ; 

void omap_connector_disable_hpd(struct drm_connector *connector)
{
	struct omap_connector *omap_connector = to_omap_connector(connector);
	struct omap_dss_device *hpd = omap_connector->hpd;

	if (hpd)
		hpd->ops->unregister_hpd_cb(hpd);
}