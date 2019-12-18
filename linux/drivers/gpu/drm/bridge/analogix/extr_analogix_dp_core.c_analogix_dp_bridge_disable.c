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
struct drm_bridge {struct analogix_dp_device* driver_private; } ;
struct analogix_dp_device {scalar_t__ dpms_mode; int fast_train_enable; int psr_supported; int /*<<< orphan*/  dev; int /*<<< orphan*/  clock; int /*<<< orphan*/  phy; TYPE_1__* plat_data; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* power_off ) (TYPE_1__*) ;scalar_t__ panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 scalar_t__ DRM_MODE_DPMS_OFF ; 
 scalar_t__ DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  POWER_ALL ; 
 int analogix_dp_prepare_panel (struct analogix_dp_device*,int,int) ; 
 int /*<<< orphan*/  analogix_dp_set_analog_power_down (struct analogix_dp_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_panel_disable (scalar_t__) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void analogix_dp_bridge_disable(struct drm_bridge *bridge)
{
	struct analogix_dp_device *dp = bridge->driver_private;
	int ret;

	if (dp->dpms_mode != DRM_MODE_DPMS_ON)
		return;

	if (dp->plat_data->panel) {
		if (drm_panel_disable(dp->plat_data->panel)) {
			DRM_ERROR("failed to disable the panel\n");
			return;
		}
	}

	disable_irq(dp->irq);

	if (dp->plat_data->power_off)
		dp->plat_data->power_off(dp->plat_data);

	analogix_dp_set_analog_power_down(dp, POWER_ALL, 1);
	phy_power_off(dp->phy);

	clk_disable_unprepare(dp->clock);

	pm_runtime_put_sync(dp->dev);

	ret = analogix_dp_prepare_panel(dp, false, true);
	if (ret)
		DRM_ERROR("failed to setup the panel ret = %d\n", ret);

	dp->fast_train_enable = false;
	dp->psr_supported = false;
	dp->dpms_mode = DRM_MODE_DPMS_OFF;
}