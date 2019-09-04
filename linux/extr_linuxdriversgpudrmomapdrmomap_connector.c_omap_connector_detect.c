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
struct omap_dss_driver {scalar_t__ (* detect ) (struct omap_dss_device*) ;} ;
struct omap_dss_device {scalar_t__ type; int /*<<< orphan*/  name; struct omap_dss_driver* driver; } ;
struct omap_connector {struct omap_dss_device* dssdev; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 scalar_t__ OMAP_DISPLAY_TYPE_DBI ; 
 scalar_t__ OMAP_DISPLAY_TYPE_DPI ; 
 scalar_t__ OMAP_DISPLAY_TYPE_DSI ; 
 scalar_t__ OMAP_DISPLAY_TYPE_SDI ; 
 int /*<<< orphan*/  VERB (char*,int /*<<< orphan*/ ,int,int) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int connector_status_unknown ; 
 scalar_t__ stub1 (struct omap_dss_device*) ; 
 struct omap_connector* to_omap_connector (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status omap_connector_detect(
		struct drm_connector *connector, bool force)
{
	struct omap_connector *omap_connector = to_omap_connector(connector);
	struct omap_dss_device *dssdev = omap_connector->dssdev;
	struct omap_dss_driver *dssdrv = dssdev->driver;
	enum drm_connector_status ret;

	if (dssdrv->detect) {
		if (dssdrv->detect(dssdev))
			ret = connector_status_connected;
		else
			ret = connector_status_disconnected;
	} else if (dssdev->type == OMAP_DISPLAY_TYPE_DPI ||
			dssdev->type == OMAP_DISPLAY_TYPE_DBI ||
			dssdev->type == OMAP_DISPLAY_TYPE_SDI ||
			dssdev->type == OMAP_DISPLAY_TYPE_DSI) {
		ret = connector_status_connected;
	} else {
		ret = connector_status_unknown;
	}

	VERB("%s: %d (force=%d)", omap_connector->dssdev->name, ret, force);

	return ret;
}