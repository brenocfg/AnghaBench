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
struct ps8622_bridge {int enabled; int /*<<< orphan*/  gpio_rst; scalar_t__ v12; int /*<<< orphan*/  panel; int /*<<< orphan*/  gpio_slp; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int PS8622_POWER_FALL_T16_MAX_US ; 
 int /*<<< orphan*/  PS8622_POWER_OFF_T17_MS ; 
 struct ps8622_bridge* bridge_to_ps8622 (struct drm_bridge*) ; 
 scalar_t__ drm_panel_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ps8622_post_disable(struct drm_bridge *bridge)
{
	struct ps8622_bridge *ps8622 = bridge_to_ps8622(bridge);

	if (!ps8622->enabled)
		return;

	ps8622->enabled = false;

	/*
	 * This doesn't matter if the regulators are turned off, but something
	 * else might keep them on. In that case, we want to assert the slp gpio
	 * to lower power.
	 */
	gpiod_set_value(ps8622->gpio_slp, 0);

	if (drm_panel_unprepare(ps8622->panel)) {
		DRM_ERROR("failed to unprepare panel\n");
		return;
	}

	if (ps8622->v12)
		regulator_disable(ps8622->v12);

	/*
	 * Sleep for at least the amount of time that it takes the power rail to
	 * fall to prevent asserting the rst gpio from doing anything.
	 */
	usleep_range(PS8622_POWER_FALL_T16_MAX_US,
		     2 * PS8622_POWER_FALL_T16_MAX_US);
	gpiod_set_value(ps8622->gpio_rst, 0);

	msleep(PS8622_POWER_OFF_T17_MS);
}