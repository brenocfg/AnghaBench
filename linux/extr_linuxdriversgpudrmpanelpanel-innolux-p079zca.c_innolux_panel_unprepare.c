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
struct innolux_panel {int prepared; int /*<<< orphan*/  supplies; TYPE_1__* desc; int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  link; } ;
struct drm_panel {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_supplies; scalar_t__ power_down_delay; scalar_t__ sleep_mode_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_enter_sleep_mode (int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_set_display_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct innolux_panel* to_innolux_panel (struct drm_panel*) ; 

__attribute__((used)) static int innolux_panel_unprepare(struct drm_panel *panel)
{
	struct innolux_panel *innolux = to_innolux_panel(panel);
	int err;

	if (!innolux->prepared)
		return 0;

	err = mipi_dsi_dcs_set_display_off(innolux->link);
	if (err < 0)
		DRM_DEV_ERROR(panel->dev, "failed to set display off: %d\n",
			      err);

	err = mipi_dsi_dcs_enter_sleep_mode(innolux->link);
	if (err < 0) {
		DRM_DEV_ERROR(panel->dev, "failed to enter sleep mode: %d\n",
			      err);
		return err;
	}

	if (innolux->desc->sleep_mode_delay)
		msleep(innolux->desc->sleep_mode_delay);

	gpiod_set_value_cansleep(innolux->enable_gpio, 0);

	if (innolux->desc->power_down_delay)
		msleep(innolux->desc->power_down_delay);

	err = regulator_bulk_disable(innolux->desc->num_supplies,
				     innolux->supplies);
	if (err < 0)
		return err;

	innolux->prepared = false;

	return 0;
}