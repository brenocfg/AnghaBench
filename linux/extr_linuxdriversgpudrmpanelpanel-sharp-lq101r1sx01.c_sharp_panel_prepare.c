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
typedef  int /*<<< orphan*/  u8 ;
struct sharp_panel {int prepared; int /*<<< orphan*/  supply; int /*<<< orphan*/  link1; int /*<<< orphan*/  mode; int /*<<< orphan*/  link2; } ;
struct drm_panel {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_PIXEL_FMT_24BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int mipi_dsi_dcs_exit_sleep_mode (int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_set_display_on (int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_set_pixel_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int sharp_panel_write (struct sharp_panel*,int,int) ; 
 int sharp_setup_symmetrical_split (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sharp_wait_frames (struct sharp_panel*,int) ; 
 struct sharp_panel* to_sharp_panel (struct drm_panel*) ; 

__attribute__((used)) static int sharp_panel_prepare(struct drm_panel *panel)
{
	struct sharp_panel *sharp = to_sharp_panel(panel);
	u8 format = MIPI_DCS_PIXEL_FMT_24BIT;
	int err;

	if (sharp->prepared)
		return 0;

	err = regulator_enable(sharp->supply);
	if (err < 0)
		return err;

	/*
	 * According to the datasheet, the panel needs around 10 ms to fully
	 * power up. At least another 120 ms is required before exiting sleep
	 * mode to make sure the panel is ready. Throw in another 20 ms for
	 * good measure.
	 */
	msleep(150);

	err = mipi_dsi_dcs_exit_sleep_mode(sharp->link1);
	if (err < 0) {
		dev_err(panel->dev, "failed to exit sleep mode: %d\n", err);
		goto poweroff;
	}

	/*
	 * The MIPI DCS specification mandates this delay only between the
	 * exit_sleep_mode and enter_sleep_mode commands, so it isn't strictly
	 * necessary here.
	 */
	/*
	msleep(120);
	*/

	/* set left-right mode */
	err = sharp_panel_write(sharp, 0x1000, 0x2a);
	if (err < 0) {
		dev_err(panel->dev, "failed to set left-right mode: %d\n", err);
		goto poweroff;
	}

	/* enable command mode */
	err = sharp_panel_write(sharp, 0x1001, 0x01);
	if (err < 0) {
		dev_err(panel->dev, "failed to enable command mode: %d\n", err);
		goto poweroff;
	}

	err = mipi_dsi_dcs_set_pixel_format(sharp->link1, format);
	if (err < 0) {
		dev_err(panel->dev, "failed to set pixel format: %d\n", err);
		goto poweroff;
	}

	/*
	 * TODO: The device supports both left-right and even-odd split
	 * configurations, but this driver currently supports only the left-
	 * right split. To support a different mode a mechanism needs to be
	 * put in place to communicate the configuration back to the DSI host
	 * controller.
	 */
	err = sharp_setup_symmetrical_split(sharp->link1, sharp->link2,
					    sharp->mode);
	if (err < 0) {
		dev_err(panel->dev, "failed to set up symmetrical split: %d\n",
			err);
		goto poweroff;
	}

	err = mipi_dsi_dcs_set_display_on(sharp->link1);
	if (err < 0) {
		dev_err(panel->dev, "failed to set display on: %d\n", err);
		goto poweroff;
	}

	sharp->prepared = true;

	/* wait for 6 frames before continuing */
	sharp_wait_frames(sharp, 6);

	return 0;

poweroff:
	regulator_disable(sharp->supply);
	return err;
}