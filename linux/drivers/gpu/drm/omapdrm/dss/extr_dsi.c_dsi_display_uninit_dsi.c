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
struct dsi_data {int vdds_dsi_enabled; int /*<<< orphan*/  vdds_dsi_reg; int /*<<< orphan*/  pll; int /*<<< orphan*/  module_id; int /*<<< orphan*/  dss; int /*<<< orphan*/  ulps_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_CLK_SRC_FCK ; 
 int /*<<< orphan*/  dsi_cio_uninit (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_enter_ulps (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_if_enable (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_vc_enable (struct dsi_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_pll_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dss_select_dsi_clk_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_display_uninit_dsi(struct dsi_data *dsi, bool disconnect_lanes,
				   bool enter_ulps)
{
	if (enter_ulps && !dsi->ulps_enabled)
		dsi_enter_ulps(dsi);

	/* disable interface */
	dsi_if_enable(dsi, 0);
	dsi_vc_enable(dsi, 0, 0);
	dsi_vc_enable(dsi, 1, 0);
	dsi_vc_enable(dsi, 2, 0);
	dsi_vc_enable(dsi, 3, 0);

	dss_select_dsi_clk_source(dsi->dss, dsi->module_id, DSS_CLK_SRC_FCK);
	dsi_cio_uninit(dsi);
	dss_pll_disable(&dsi->pll);

	if (disconnect_lanes) {
		regulator_disable(dsi->vdds_dsi_reg);
		dsi->vdds_dsi_enabled = false;
	}
}