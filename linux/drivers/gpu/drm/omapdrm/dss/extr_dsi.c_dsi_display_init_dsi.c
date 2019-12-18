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
struct dsi_data {scalar_t__ module_id; int vdds_dsi_enabled; int /*<<< orphan*/  pll; int /*<<< orphan*/  dss; int /*<<< orphan*/  vdds_dsi_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  DSS_CLK_SRC_FCK ; 
 int /*<<< orphan*/  DSS_CLK_SRC_PLL1_2 ; 
 int /*<<< orphan*/  DSS_CLK_SRC_PLL2_2 ; 
 int /*<<< orphan*/  _dsi_print_reset_status (struct dsi_data*) ; 
 int dsi_cio_init (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_cio_uninit (struct dsi_data*) ; 
 int dsi_configure_dsi_clocks (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_force_tx_stop_mode_io (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_if_enable (struct dsi_data*,int) ; 
 int dsi_proto_config (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_proto_timings (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_set_lp_clk_divisor (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_vc_enable (struct dsi_data*,int,int) ; 
 int /*<<< orphan*/  dss_pll_disable (int /*<<< orphan*/ *) ; 
 int dss_pll_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dss_select_dsi_clk_source (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_display_init_dsi(struct dsi_data *dsi)
{
	int r;

	r = dss_pll_enable(&dsi->pll);
	if (r)
		return r;

	r = dsi_configure_dsi_clocks(dsi);
	if (r)
		goto err0;

	dss_select_dsi_clk_source(dsi->dss, dsi->module_id,
				  dsi->module_id == 0 ?
				  DSS_CLK_SRC_PLL1_2 : DSS_CLK_SRC_PLL2_2);

	DSSDBG("PLL OK\n");

	if (!dsi->vdds_dsi_enabled) {
		r = regulator_enable(dsi->vdds_dsi_reg);
		if (r)
			goto err1;

		dsi->vdds_dsi_enabled = true;
	}

	r = dsi_cio_init(dsi);
	if (r)
		goto err2;

	_dsi_print_reset_status(dsi);

	dsi_proto_timings(dsi);
	dsi_set_lp_clk_divisor(dsi);

	if (1)
		_dsi_print_reset_status(dsi);

	r = dsi_proto_config(dsi);
	if (r)
		goto err3;

	/* enable interface */
	dsi_vc_enable(dsi, 0, 1);
	dsi_vc_enable(dsi, 1, 1);
	dsi_vc_enable(dsi, 2, 1);
	dsi_vc_enable(dsi, 3, 1);
	dsi_if_enable(dsi, 1);
	dsi_force_tx_stop_mode_io(dsi);

	return 0;
err3:
	dsi_cio_uninit(dsi);
err2:
	regulator_disable(dsi->vdds_dsi_reg);
	dsi->vdds_dsi_enabled = false;
err1:
	dss_select_dsi_clk_source(dsi->dss, dsi->module_id, DSS_CLK_SRC_FCK);
err0:
	dss_pll_disable(&dsi->pll);

	return r;
}