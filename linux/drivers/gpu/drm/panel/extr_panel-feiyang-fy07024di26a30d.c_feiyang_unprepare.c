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
struct feiyang {int /*<<< orphan*/  dvdd; int /*<<< orphan*/  avdd; int /*<<< orphan*/  reset; int /*<<< orphan*/  dsi; } ;
struct drm_panel {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_enter_sleep_mode (int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_set_display_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct feiyang* panel_to_feiyang (struct drm_panel*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int feiyang_unprepare(struct drm_panel *panel)
{
	struct feiyang *ctx = panel_to_feiyang(panel);
	int ret;

	ret = mipi_dsi_dcs_set_display_off(ctx->dsi);
	if (ret < 0)
		DRM_DEV_ERROR(panel->dev, "failed to set display off: %d\n",
			      ret);

	ret = mipi_dsi_dcs_enter_sleep_mode(ctx->dsi);
	if (ret < 0)
		DRM_DEV_ERROR(panel->dev, "failed to enter sleep mode: %d\n",
			      ret);

	/* T13 (backlight fall + video & logic signal fall) T13 >= 200ms */
	msleep(200);

	gpiod_set_value(ctx->reset, 0);

	regulator_disable(ctx->avdd);

	/* T11 (dvdd rise to fall) 0 < T11 <= 10ms  */
	msleep(10);

	regulator_disable(ctx->dvdd);

	return 0;
}