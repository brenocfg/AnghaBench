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
struct ps8622_bridge {int enabled; int /*<<< orphan*/  gpio_rst; int /*<<< orphan*/  gpio_slp; int /*<<< orphan*/  panel; scalar_t__ v12; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int PS8622_POWER_RISE_T1_MAX_US ; 
 int PS8622_POWER_RISE_T1_MIN_US ; 
 int PS8622_RST_HIGH_T2_MAX_US ; 
 int PS8622_RST_HIGH_T2_MIN_US ; 
 struct ps8622_bridge* bridge_to_ps8622 (struct drm_bridge*) ; 
 scalar_t__ drm_panel_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int ps8622_send_config (struct ps8622_bridge*) ; 
 int regulator_enable (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ps8622_pre_enable(struct drm_bridge *bridge)
{
	struct ps8622_bridge *ps8622 = bridge_to_ps8622(bridge);
	int ret;

	if (ps8622->enabled)
		return;

	gpiod_set_value(ps8622->gpio_rst, 0);

	if (ps8622->v12) {
		ret = regulator_enable(ps8622->v12);
		if (ret)
			DRM_ERROR("fails to enable ps8622->v12");
	}

	if (drm_panel_prepare(ps8622->panel)) {
		DRM_ERROR("failed to prepare panel\n");
		return;
	}

	gpiod_set_value(ps8622->gpio_slp, 1);

	/*
	 * T1 is the range of time that it takes for the power to rise after we
	 * enable the lcd/ps8622 fet. T2 is the range of time in which the
	 * data sheet specifies we should deassert the reset pin.
	 *
	 * If it takes T1.max for the power to rise, we need to wait atleast
	 * T2.min before deasserting the reset pin. If it takes T1.min for the
	 * power to rise, we need to wait at most T2.max before deasserting the
	 * reset pin.
	 */
	usleep_range(PS8622_RST_HIGH_T2_MIN_US + PS8622_POWER_RISE_T1_MAX_US,
		     PS8622_RST_HIGH_T2_MAX_US + PS8622_POWER_RISE_T1_MIN_US);

	gpiod_set_value(ps8622->gpio_rst, 1);

	/* wait 20ms after RST high */
	usleep_range(20000, 30000);

	ret = ps8622_send_config(ps8622);
	if (ret) {
		DRM_ERROR("Failed to send config to bridge (%d)\n", ret);
		return;
	}

	ps8622->enabled = true;
}