#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct omap_dss_device {int ops_flags; struct omap_dss_device* next; } ;
struct omap_connector {struct omap_dss_device* output; } ;
struct drm_connector {int dummy; } ;
typedef  enum omap_dss_device_ops_flag { ____Placeholder_omap_dss_device_ops_flag } omap_dss_device_ops_flag ;

/* Variables and functions */
 struct omap_connector* to_omap_connector (struct drm_connector*) ; 

__attribute__((used)) static struct omap_dss_device *
omap_connector_find_device(struct drm_connector *connector,
			   enum omap_dss_device_ops_flag op)
{
	struct omap_connector *omap_connector = to_omap_connector(connector);
	struct omap_dss_device *dssdev = NULL;
	struct omap_dss_device *d;

	for (d = omap_connector->output; d; d = d->next) {
		if (d->ops_flags & op)
			dssdev = d;
	}

	return dssdev;
}