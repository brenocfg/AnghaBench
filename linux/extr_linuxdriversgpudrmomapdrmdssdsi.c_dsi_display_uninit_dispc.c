#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dispc_channel; } ;
struct dsi_data {scalar_t__ mode; int /*<<< orphan*/  dss; TYPE_1__ output; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_CLK_SRC_FCK ; 
 scalar_t__ OMAP_DSS_DSI_CMD_MODE ; 
 int /*<<< orphan*/  dsi_framedone_irq_callback ; 
 int /*<<< orphan*/  dss_mgr_unregister_framedone_handler (TYPE_1__*,int /*<<< orphan*/ ,struct dsi_data*) ; 
 int /*<<< orphan*/  dss_select_lcd_clk_source (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_display_uninit_dispc(struct dsi_data *dsi)
{
	enum omap_channel channel = dsi->output.dispc_channel;

	if (dsi->mode == OMAP_DSS_DSI_CMD_MODE)
		dss_mgr_unregister_framedone_handler(&dsi->output,
				dsi_framedone_irq_callback, dsi);

	dss_select_lcd_clk_source(dsi->dss, channel, DSS_CLK_SRC_FCK);
}