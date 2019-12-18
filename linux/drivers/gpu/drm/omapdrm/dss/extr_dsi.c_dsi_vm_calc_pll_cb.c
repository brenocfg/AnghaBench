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
struct dsi_data {TYPE_1__* data; } ;
struct TYPE_4__ {int n; int m; unsigned long fint; unsigned long clkdco; } ;
struct dsi_clk_calc_ctx {int /*<<< orphan*/  req_pck_min; int /*<<< orphan*/  pll; TYPE_2__ dsi_cinfo; struct dsi_data* dsi; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_fck_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsi_vm_calc_hsdiv_cb ; 
 int dss_pll_hsdiv_calc_a (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dsi_clk_calc_ctx*) ; 

__attribute__((used)) static bool dsi_vm_calc_pll_cb(int n, int m, unsigned long fint,
		unsigned long clkdco, void *data)
{
	struct dsi_clk_calc_ctx *ctx = data;
	struct dsi_data *dsi = ctx->dsi;

	ctx->dsi_cinfo.n = n;
	ctx->dsi_cinfo.m = m;
	ctx->dsi_cinfo.fint = fint;
	ctx->dsi_cinfo.clkdco = clkdco;

	return dss_pll_hsdiv_calc_a(ctx->pll, clkdco, ctx->req_pck_min,
			dsi->data->max_fck_freq,
			dsi_vm_calc_hsdiv_cb, ctx);
}