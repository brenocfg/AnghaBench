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
struct s6d16d0 {int /*<<< orphan*/  dev; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  supply; } ;
struct mipi_dsi_device {int dummy; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MIPI_DSI_DCS_TEAR_MODE_VBLANK ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int mipi_dsi_dcs_exit_sleep_mode (struct mipi_dsi_device*) ; 
 int mipi_dsi_dcs_set_tear_on (struct mipi_dsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct s6d16d0* panel_to_s6d16d0 (struct drm_panel*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int s6d16d0_prepare(struct drm_panel *panel)
{
	struct s6d16d0 *s6 = panel_to_s6d16d0(panel);
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(s6->dev);
	int ret;

	ret = regulator_enable(s6->supply);
	if (ret) {
		DRM_DEV_ERROR(s6->dev, "failed to enable supply (%d)\n", ret);
		return ret;
	}

	/* Assert RESET */
	gpiod_set_value_cansleep(s6->reset_gpio, 1);
	udelay(10);
	/* De-assert RESET */
	gpiod_set_value_cansleep(s6->reset_gpio, 0);
	msleep(120);

	/* Enabe tearing mode: send TE (tearing effect) at VBLANK */
	ret = mipi_dsi_dcs_set_tear_on(dsi,
				       MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	if (ret) {
		DRM_DEV_ERROR(s6->dev, "failed to enable vblank TE (%d)\n",
			      ret);
		return ret;
	}
	/* Exit sleep mode and power on */
	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret) {
		DRM_DEV_ERROR(s6->dev, "failed to exit sleep mode (%d)\n",
			      ret);
		return ret;
	}

	return 0;
}