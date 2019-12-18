#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  encoder; } ;
struct TYPE_9__ {int bus_flags; } ;
struct TYPE_8__ {int polled; TYPE_3__ display_info; } ;
struct tc_data {scalar_t__ hpd_pin; TYPE_1__ bridge; TYPE_2__ connector; scalar_t__ panel; scalar_t__ have_irq; } ;
struct drm_device {int dummy; } ;
struct drm_bridge {struct drm_device* dev; } ;

/* Variables and functions */
 int DRM_BUS_FLAG_DE_HIGH ; 
 int DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE ; 
 int DRM_BUS_FLAG_SYNC_DRIVE_NEGEDGE ; 
 int DRM_CONNECTOR_POLL_CONNECT ; 
 int DRM_CONNECTOR_POLL_DISCONNECT ; 
 int DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DisplayPort ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_eDP ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_RGB888_1X24 ; 
 struct tc_data* bridge_to_tc (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_display_info_set_bus_formats (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_panel_attach (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  tc_connector_funcs ; 
 int /*<<< orphan*/  tc_connector_helper_funcs ; 

__attribute__((used)) static int tc_bridge_attach(struct drm_bridge *bridge)
{
	u32 bus_format = MEDIA_BUS_FMT_RGB888_1X24;
	struct tc_data *tc = bridge_to_tc(bridge);
	struct drm_device *drm = bridge->dev;
	int ret;

	/* Create DP/eDP connector */
	drm_connector_helper_add(&tc->connector, &tc_connector_helper_funcs);
	ret = drm_connector_init(drm, &tc->connector, &tc_connector_funcs,
				 tc->panel ? DRM_MODE_CONNECTOR_eDP :
				 DRM_MODE_CONNECTOR_DisplayPort);
	if (ret)
		return ret;

	/* Don't poll if don't have HPD connected */
	if (tc->hpd_pin >= 0) {
		if (tc->have_irq)
			tc->connector.polled = DRM_CONNECTOR_POLL_HPD;
		else
			tc->connector.polled = DRM_CONNECTOR_POLL_CONNECT |
					       DRM_CONNECTOR_POLL_DISCONNECT;
	}

	if (tc->panel)
		drm_panel_attach(tc->panel, &tc->connector);

	drm_display_info_set_bus_formats(&tc->connector.display_info,
					 &bus_format, 1);
	tc->connector.display_info.bus_flags =
		DRM_BUS_FLAG_DE_HIGH |
		DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE |
		DRM_BUS_FLAG_SYNC_DRIVE_NEGEDGE;
	drm_connector_attach_encoder(&tc->connector, tc->bridge.encoder);

	return 0;
}