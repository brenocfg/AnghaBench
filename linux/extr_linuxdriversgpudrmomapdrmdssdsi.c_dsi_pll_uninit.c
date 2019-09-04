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
struct dsi_data {int vdds_dsi_enabled; int /*<<< orphan*/  vdds_dsi_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_PLL_POWER_OFF ; 
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dsi_disable_scp_clk (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_pll_power (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_runtime_put (struct dsi_data*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_pll_uninit(struct dsi_data *dsi, bool disconnect_lanes)
{
	dsi_pll_power(dsi, DSI_PLL_POWER_OFF);
	if (disconnect_lanes) {
		WARN_ON(!dsi->vdds_dsi_enabled);
		regulator_disable(dsi->vdds_dsi_reg);
		dsi->vdds_dsi_enabled = false;
	}

	dsi_disable_scp_clk(dsi);
	dsi_runtime_put(dsi);

	DSSDBG("PLL uninit done\n");
}