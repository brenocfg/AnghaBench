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
struct seq_file {struct dsi_data* private; } ;
struct dss_pll_clock_info {int clkdco; int /*<<< orphan*/ * mX; int /*<<< orphan*/ * clkout; int /*<<< orphan*/  m; int /*<<< orphan*/  n; int /*<<< orphan*/  fint; } ;
struct dss_pll {int /*<<< orphan*/  clkin; struct dss_pll_clock_info cinfo; } ;
struct TYPE_2__ {int lp_clk; } ;
struct dsi_data {int module_id; TYPE_1__ current_lp_cinfo; int /*<<< orphan*/  dss; struct dss_pll pll; } ;
typedef  enum dss_clk_source { ____Placeholder_dss_clk_source } dss_clk_source ;

/* Variables and functions */
 int DSS_CLK_SRC_FCK ; 
 int DSS_CLK_SRC_PLL1_1 ; 
 int DSS_CLK_SRC_PLL1_2 ; 
 int DSS_CLK_SRC_PLL2_1 ; 
 int DSS_CLK_SRC_PLL2_2 ; 
 size_t HSDIV_DISPC ; 
 size_t HSDIV_DSI ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int dsi_fclk_rate (struct dsi_data*) ; 
 int dsi_get_txbyteclkhs (struct dsi_data*) ; 
 scalar_t__ dsi_runtime_get (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_runtime_put (struct dsi_data*) ; 
 int dss_get_clk_source_name (int) ; 
 int dss_get_dispc_clk_source (int /*<<< orphan*/ ) ; 
 int dss_get_dsi_clk_source (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 

__attribute__((used)) static int dsi_dump_dsi_clocks(struct seq_file *s, void *p)
{
	struct dsi_data *dsi = s->private;
	struct dss_pll_clock_info *cinfo = &dsi->pll.cinfo;
	enum dss_clk_source dispc_clk_src, dsi_clk_src;
	int dsi_module = dsi->module_id;
	struct dss_pll *pll = &dsi->pll;

	dispc_clk_src = dss_get_dispc_clk_source(dsi->dss);
	dsi_clk_src = dss_get_dsi_clk_source(dsi->dss, dsi_module);

	if (dsi_runtime_get(dsi))
		return 0;

	seq_printf(s,	"- DSI%d PLL -\n", dsi_module + 1);

	seq_printf(s,	"dsi pll clkin\t%lu\n", clk_get_rate(pll->clkin));

	seq_printf(s,	"Fint\t\t%-16lun %u\n", cinfo->fint, cinfo->n);

	seq_printf(s,	"CLKIN4DDR\t%-16lum %u\n",
			cinfo->clkdco, cinfo->m);

	seq_printf(s,	"DSI_PLL_HSDIV_DISPC (%s)\t%-16lum_dispc %u\t(%s)\n",
			dss_get_clk_source_name(dsi_module == 0 ?
				DSS_CLK_SRC_PLL1_1 :
				DSS_CLK_SRC_PLL2_1),
			cinfo->clkout[HSDIV_DISPC],
			cinfo->mX[HSDIV_DISPC],
			dispc_clk_src == DSS_CLK_SRC_FCK ?
			"off" : "on");

	seq_printf(s,	"DSI_PLL_HSDIV_DSI (%s)\t%-16lum_dsi %u\t(%s)\n",
			dss_get_clk_source_name(dsi_module == 0 ?
				DSS_CLK_SRC_PLL1_2 :
				DSS_CLK_SRC_PLL2_2),
			cinfo->clkout[HSDIV_DSI],
			cinfo->mX[HSDIV_DSI],
			dsi_clk_src == DSS_CLK_SRC_FCK ?
			"off" : "on");

	seq_printf(s,	"- DSI%d -\n", dsi_module + 1);

	seq_printf(s,	"dsi fclk source = %s\n",
			dss_get_clk_source_name(dsi_clk_src));

	seq_printf(s,	"DSI_FCLK\t%lu\n", dsi_fclk_rate(dsi));

	seq_printf(s,	"DDR_CLK\t\t%lu\n",
			cinfo->clkdco / 4);

	seq_printf(s,	"TxByteClkHS\t%lu\n", dsi_get_txbyteclkhs(dsi));

	seq_printf(s,	"LP_CLK\t\t%lu\n", dsi->current_lp_cinfo.lp_clk);

	dsi_runtime_put(dsi);

	return 0;
}