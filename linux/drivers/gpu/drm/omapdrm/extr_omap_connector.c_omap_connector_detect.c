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
struct drm_connector {int connector_type; int /*<<< orphan*/  name; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;
struct TYPE_2__ {scalar_t__ (* detect ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
#define  DRM_MODE_CONNECTOR_DPI 130 
#define  DRM_MODE_CONNECTOR_DSI 129 
#define  DRM_MODE_CONNECTOR_LVDS 128 
 int /*<<< orphan*/  OMAP_DSS_DEVICE_OP_DETECT ; 
 int /*<<< orphan*/  VERB (char*,int /*<<< orphan*/ ,int,int) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int connector_status_unknown ; 
 struct omap_dss_device* omap_connector_find_device (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_connector_hpd_notify (struct drm_connector*,int) ; 
 scalar_t__ stub1 (struct omap_dss_device*) ; 

__attribute__((used)) static enum drm_connector_status omap_connector_detect(
		struct drm_connector *connector, bool force)
{
	struct omap_dss_device *dssdev;
	enum drm_connector_status status;

	dssdev = omap_connector_find_device(connector,
					    OMAP_DSS_DEVICE_OP_DETECT);

	if (dssdev) {
		status = dssdev->ops->detect(dssdev)
		       ? connector_status_connected
		       : connector_status_disconnected;

		omap_connector_hpd_notify(connector, status);
	} else {
		switch (connector->connector_type) {
		case DRM_MODE_CONNECTOR_DPI:
		case DRM_MODE_CONNECTOR_LVDS:
		case DRM_MODE_CONNECTOR_DSI:
			status = connector_status_connected;
			break;
		default:
			status = connector_status_unknown;
			break;
		}
	}

	VERB("%s: %d (force=%d)", connector->name, status, force);

	return status;
}