#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct s6e63j0x03 {TYPE_2__* bl_dev; int /*<<< orphan*/  dev; } ;
struct mipi_dsi_device {int dummy; } ;
struct drm_panel {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  power; } ;
struct TYPE_4__ {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_NORMAL ; 
 int mipi_dsi_dcs_enter_sleep_mode (struct mipi_dsi_device*) ; 
 int mipi_dsi_dcs_set_display_off (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct s6e63j0x03* panel_to_s6e63j0x03 (struct drm_panel*) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s6e63j0x03_disable(struct drm_panel *panel)
{
	struct s6e63j0x03 *ctx = panel_to_s6e63j0x03(panel);
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int ret;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0)
		return ret;

	ctx->bl_dev->props.power = FB_BLANK_NORMAL;

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0)
		return ret;

	msleep(120);

	return 0;
}