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
struct s6d16d0 {int /*<<< orphan*/  supply; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  dev; } ;
struct mipi_dsi_device {int dummy; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int mipi_dsi_dcs_enter_sleep_mode (struct mipi_dsi_device*) ; 
 struct s6d16d0* panel_to_s6d16d0 (struct drm_panel*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s6d16d0_unprepare(struct drm_panel *panel)
{
	struct s6d16d0 *s6 = panel_to_s6d16d0(panel);
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(s6->dev);
	int ret;

	/* Enter sleep mode */
	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret) {
		DRM_DEV_ERROR(s6->dev, "failed to enter sleep mode (%d)\n",
			      ret);
		return ret;
	}

	/* Assert RESET */
	gpiod_set_value_cansleep(s6->reset_gpio, 1);
	regulator_disable(s6->supply);

	return 0;
}