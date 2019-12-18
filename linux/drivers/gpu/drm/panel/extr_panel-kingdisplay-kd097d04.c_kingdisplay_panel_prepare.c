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
struct kingdisplay_panel_cmd {int dummy; } ;
struct kingdisplay_panel {int prepared; int /*<<< orphan*/  supply; int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  link; } ;
struct drm_panel {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * init_code ; 
 int mipi_dsi_dcs_exit_sleep_mode (int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_set_display_on (int /*<<< orphan*/ ) ; 
 int mipi_dsi_generic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct kingdisplay_panel* to_kingdisplay_panel (struct drm_panel*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int kingdisplay_panel_prepare(struct drm_panel *panel)
{
	struct kingdisplay_panel *kingdisplay = to_kingdisplay_panel(panel);
	int err, regulator_err;
	unsigned int i;

	if (kingdisplay->prepared)
		return 0;

	gpiod_set_value_cansleep(kingdisplay->enable_gpio, 0);

	err = regulator_enable(kingdisplay->supply);
	if (err < 0)
		return err;

	/* T2: 15ms */
	usleep_range(15000, 16000);

	gpiod_set_value_cansleep(kingdisplay->enable_gpio, 1);

	/* T4: 15ms */
	usleep_range(15000, 16000);

	for (i = 0; i < ARRAY_SIZE(init_code); i++) {
		err = mipi_dsi_generic_write(kingdisplay->link, &init_code[i],
					sizeof(struct kingdisplay_panel_cmd));
		if (err < 0) {
			DRM_DEV_ERROR(panel->dev, "failed write init cmds: %d\n",
				      err);
			goto poweroff;
		}
	}

	err = mipi_dsi_dcs_exit_sleep_mode(kingdisplay->link);
	if (err < 0) {
		DRM_DEV_ERROR(panel->dev, "failed to exit sleep mode: %d\n",
			      err);
		goto poweroff;
	}

	/* T6: 120ms */
	msleep(120);

	err = mipi_dsi_dcs_set_display_on(kingdisplay->link);
	if (err < 0) {
		DRM_DEV_ERROR(panel->dev, "failed to set display on: %d\n",
			      err);
		goto poweroff;
	}

	/* T7: 10ms */
	usleep_range(10000, 11000);

	kingdisplay->prepared = true;

	return 0;

poweroff:
	gpiod_set_value_cansleep(kingdisplay->enable_gpio, 0);

	regulator_err = regulator_disable(kingdisplay->supply);
	if (regulator_err)
		DRM_DEV_ERROR(panel->dev, "failed to disable regulator: %d\n",
			      regulator_err);

	return err;
}