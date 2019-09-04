#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dpi_data {TYPE_3__* pll; int /*<<< orphan*/  clk_src; } ;
struct TYPE_7__ {int lck_div; int pck_div; int /*<<< orphan*/  lck; int /*<<< orphan*/  pck; } ;
struct TYPE_9__ {int /*<<< orphan*/ * clkout; } ;
struct dpi_clk_calc_ctx {unsigned long pck_min; unsigned long pck_max; TYPE_2__ dispc_cinfo; TYPE_4__ pll_cinfo; struct dpi_data* dpi; int /*<<< orphan*/  clkout_idx; } ;
struct TYPE_8__ {TYPE_1__* hw; int /*<<< orphan*/  clkin; } ;
struct TYPE_6__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DSS_PLL_TYPE_A ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpi_calc_pll_cb ; 
 int dss_pll_calc_a (TYPE_3__*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,struct dpi_clk_calc_ctx*) ; 
 int /*<<< orphan*/  dss_pll_calc_b (TYPE_3__*,unsigned long,unsigned long,TYPE_4__*) ; 
 int /*<<< orphan*/  dss_pll_get_clkout_idx_for_src (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dpi_clk_calc_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool dpi_pll_clk_calc(struct dpi_data *dpi, unsigned long pck,
		struct dpi_clk_calc_ctx *ctx)
{
	unsigned long clkin;

	memset(ctx, 0, sizeof(*ctx));
	ctx->dpi = dpi;
	ctx->clkout_idx = dss_pll_get_clkout_idx_for_src(dpi->clk_src);

	clkin = clk_get_rate(dpi->pll->clkin);

	if (dpi->pll->hw->type == DSS_PLL_TYPE_A) {
		unsigned long pll_min, pll_max;

		ctx->pck_min = pck - 1000;
		ctx->pck_max = pck + 1000;

		pll_min = 0;
		pll_max = 0;

		return dss_pll_calc_a(ctx->dpi->pll, clkin,
				pll_min, pll_max,
				dpi_calc_pll_cb, ctx);
	} else { /* DSS_PLL_TYPE_B */
		dss_pll_calc_b(dpi->pll, clkin, pck, &ctx->pll_cinfo);

		ctx->dispc_cinfo.lck_div = 1;
		ctx->dispc_cinfo.pck_div = 1;
		ctx->dispc_cinfo.lck = ctx->pll_cinfo.clkout[0];
		ctx->dispc_cinfo.pck = ctx->dispc_cinfo.lck;

		return true;
	}
}