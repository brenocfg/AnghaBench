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
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ddc; } ;
struct analogix_dp_device {TYPE_2__* plat_data; int /*<<< orphan*/  connector; int /*<<< orphan*/  dev; TYPE_1__ aux; } ;
struct TYPE_4__ {scalar_t__ (* get_modes ) (TYPE_2__*,struct drm_connector*) ;scalar_t__ panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int analogix_dp_prepare_panel (struct analogix_dp_device*,int,int) ; 
 scalar_t__ drm_add_edid_modes (int /*<<< orphan*/ *,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (int /*<<< orphan*/ *,struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 
 scalar_t__ drm_panel_get_modes (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_2__*,struct drm_connector*) ; 
 struct analogix_dp_device* to_dp (struct drm_connector*) ; 

__attribute__((used)) static int analogix_dp_get_modes(struct drm_connector *connector)
{
	struct analogix_dp_device *dp = to_dp(connector);
	struct edid *edid;
	int ret, num_modes = 0;

	if (dp->plat_data->panel) {
		num_modes += drm_panel_get_modes(dp->plat_data->panel);
	} else {
		ret = analogix_dp_prepare_panel(dp, true, false);
		if (ret) {
			DRM_ERROR("Failed to prepare panel (%d)\n", ret);
			return 0;
		}

		pm_runtime_get_sync(dp->dev);
		edid = drm_get_edid(connector, &dp->aux.ddc);
		pm_runtime_put(dp->dev);
		if (edid) {
			drm_connector_update_edid_property(&dp->connector,
							   edid);
			num_modes += drm_add_edid_modes(&dp->connector, edid);
			kfree(edid);
		}

		ret = analogix_dp_prepare_panel(dp, false, false);
		if (ret)
			DRM_ERROR("Failed to unprepare panel (%d)\n", ret);
	}

	if (dp->plat_data->get_modes)
		num_modes += dp->plat_data->get_modes(dp->plat_data, connector);

	return num_modes;
}