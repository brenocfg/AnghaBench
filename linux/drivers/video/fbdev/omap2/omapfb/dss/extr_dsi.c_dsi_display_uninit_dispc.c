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
struct platform_device {int dummy; } ;
struct omap_overlay_manager {int /*<<< orphan*/  id; } ;
struct dsi_data {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_DSS_CLK_SRC_FCK ; 
 scalar_t__ OMAP_DSS_DSI_CMD_MODE ; 
 int /*<<< orphan*/  dsi_framedone_irq_callback ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dss_mgr_unregister_framedone_handler (struct omap_overlay_manager*,int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  dss_select_lcd_clk_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_display_uninit_dispc(struct platform_device *dsidev,
		struct omap_overlay_manager *mgr)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);

	if (dsi->mode == OMAP_DSS_DSI_CMD_MODE)
		dss_mgr_unregister_framedone_handler(mgr,
				dsi_framedone_irq_callback, dsidev);

	dss_select_lcd_clk_source(mgr->id, OMAP_DSS_CLK_SRC_FCK);
}