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
struct otm8009a {int enabled; int /*<<< orphan*/  bl_dev; int /*<<< orphan*/  dev; } ;
struct mipi_dsi_device {int dummy; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_disable (int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_enter_sleep_mode (struct mipi_dsi_device*) ; 
 int mipi_dsi_dcs_set_display_off (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct otm8009a* panel_to_otm8009a (struct drm_panel*) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int otm8009a_disable(struct drm_panel *panel)
{
	struct otm8009a *ctx = panel_to_otm8009a(panel);
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int ret;

	if (!ctx->enabled)
		return 0; /* This is not an issue so we return 0 here */

	backlight_disable(ctx->bl_dev);

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret)
		return ret;

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret)
		return ret;

	msleep(120);

	ctx->enabled = false;

	return 0;
}