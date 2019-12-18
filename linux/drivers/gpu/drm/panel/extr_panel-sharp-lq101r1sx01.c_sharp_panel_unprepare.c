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
struct sharp_panel {int prepared; int /*<<< orphan*/  supply; int /*<<< orphan*/  link1; } ;
struct drm_panel {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int mipi_dsi_dcs_enter_sleep_mode (int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_set_display_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sharp_wait_frames (struct sharp_panel*,int) ; 
 struct sharp_panel* to_sharp_panel (struct drm_panel*) ; 

__attribute__((used)) static int sharp_panel_unprepare(struct drm_panel *panel)
{
	struct sharp_panel *sharp = to_sharp_panel(panel);
	int err;

	if (!sharp->prepared)
		return 0;

	sharp_wait_frames(sharp, 4);

	err = mipi_dsi_dcs_set_display_off(sharp->link1);
	if (err < 0)
		dev_err(panel->dev, "failed to set display off: %d\n", err);

	err = mipi_dsi_dcs_enter_sleep_mode(sharp->link1);
	if (err < 0)
		dev_err(panel->dev, "failed to enter sleep mode: %d\n", err);

	msleep(120);

	regulator_disable(sharp->supply);

	sharp->prepared = false;

	return 0;
}