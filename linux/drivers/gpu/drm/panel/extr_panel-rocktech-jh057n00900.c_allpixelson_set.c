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
typedef  int u64 ;
struct mipi_dsi_device {int dummy; } ;
struct jh057n {int /*<<< orphan*/  panel; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_DRIVER (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ST7703_CMD_ALL_PIXEL_ON ; 
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsi_generic_write_seq (struct mipi_dsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allpixelson_set(void *data, u64 val)
{
	struct jh057n *ctx = data;
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	DRM_DEV_DEBUG_DRIVER(ctx->dev, "Setting all pixels on\n");
	dsi_generic_write_seq(dsi, ST7703_CMD_ALL_PIXEL_ON);
	msleep(val * 1000);
	/* Reset the panel to get video back */
	drm_panel_disable(&ctx->panel);
	drm_panel_unprepare(&ctx->panel);
	drm_panel_prepare(&ctx->panel);
	drm_panel_enable(&ctx->panel);

	return 0;
}