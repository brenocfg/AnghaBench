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
struct TYPE_4__ {int n; int m; unsigned long fint; unsigned long clkdco; } ;
struct dpi_clk_calc_ctx {TYPE_1__* dpi; int /*<<< orphan*/  pck_min; TYPE_2__ pll_cinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  dss; int /*<<< orphan*/  pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpi_calc_hsdiv_cb ; 
 int /*<<< orphan*/  dss_get_max_fck_rate (int /*<<< orphan*/ ) ; 
 int dss_pll_hsdiv_calc_a (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpi_clk_calc_ctx*) ; 

__attribute__((used)) static bool dpi_calc_pll_cb(int n, int m, unsigned long fint,
		unsigned long clkdco,
		void *data)
{
	struct dpi_clk_calc_ctx *ctx = data;

	ctx->pll_cinfo.n = n;
	ctx->pll_cinfo.m = m;
	ctx->pll_cinfo.fint = fint;
	ctx->pll_cinfo.clkdco = clkdco;

	return dss_pll_hsdiv_calc_a(ctx->dpi->pll, clkdco,
		ctx->pck_min, dss_get_max_fck_rate(ctx->dpi->dss),
		dpi_calc_hsdiv_cb, ctx);
}