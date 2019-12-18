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
struct kingdisplay_panel {int prepared; int /*<<< orphan*/  supply; int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  link; } ;
struct drm_panel {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_enter_sleep_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 struct kingdisplay_panel* to_kingdisplay_panel (struct drm_panel*) ; 

__attribute__((used)) static int kingdisplay_panel_unprepare(struct drm_panel *panel)
{
	struct kingdisplay_panel *kingdisplay = to_kingdisplay_panel(panel);
	int err;

	if (!kingdisplay->prepared)
		return 0;

	err = mipi_dsi_dcs_enter_sleep_mode(kingdisplay->link);
	if (err < 0) {
		DRM_DEV_ERROR(panel->dev, "failed to enter sleep mode: %d\n",
			      err);
		return err;
	}

	/* T15: 120ms */
	msleep(120);

	gpiod_set_value_cansleep(kingdisplay->enable_gpio, 0);

	err = regulator_disable(kingdisplay->supply);
	if (err < 0)
		return err;

	kingdisplay->prepared = false;

	return 0;
}