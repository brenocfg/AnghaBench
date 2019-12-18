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
typedef  int u64 ;
struct videomode {scalar_t__ pixelclock; } ;
struct omap_dss_dsi_config {int hs_clk_min; scalar_t__ trans_mode; int hs_clk_max; int /*<<< orphan*/  pixel_format; struct videomode* vm; } ;
struct TYPE_2__ {int /*<<< orphan*/  clkin; } ;
struct dsi_data {int num_lanes_used; TYPE_1__ pll; } ;
struct dsi_clk_calc_ctx {TYPE_1__* pll; scalar_t__ req_pck_max; scalar_t__ req_pck_min; scalar_t__ req_pck_nom; struct omap_dss_dsi_config const* config; struct dsi_data* dsi; } ;

/* Variables and functions */
 scalar_t__ OMAP_DSS_DSI_BURST_MODE ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long div64_u64 (int,int) ; 
 int dsi_get_pixel_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_vm_calc_pll_cb ; 
 int dss_pll_calc_a (TYPE_1__*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,struct dsi_clk_calc_ctx*) ; 
 unsigned long max (int,unsigned long) ; 
 int /*<<< orphan*/  memset (struct dsi_clk_calc_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool dsi_vm_calc(struct dsi_data *dsi,
		const struct omap_dss_dsi_config *cfg,
		struct dsi_clk_calc_ctx *ctx)
{
	const struct videomode *vm = cfg->vm;
	unsigned long clkin;
	unsigned long pll_min;
	unsigned long pll_max;
	int ndl = dsi->num_lanes_used - 1;
	int bitspp = dsi_get_pixel_size(cfg->pixel_format);
	unsigned long byteclk_min;

	clkin = clk_get_rate(dsi->pll.clkin);

	memset(ctx, 0, sizeof(*ctx));
	ctx->dsi = dsi;
	ctx->pll = &dsi->pll;
	ctx->config = cfg;

	/* these limits should come from the panel driver */
	ctx->req_pck_min = vm->pixelclock - 1000;
	ctx->req_pck_nom = vm->pixelclock;
	ctx->req_pck_max = vm->pixelclock + 1000;

	byteclk_min = div64_u64((u64)ctx->req_pck_min * bitspp, ndl * 8);
	pll_min = max(cfg->hs_clk_min * 4, byteclk_min * 4 * 4);

	if (cfg->trans_mode == OMAP_DSS_DSI_BURST_MODE) {
		pll_max = cfg->hs_clk_max * 4;
	} else {
		unsigned long byteclk_max;
		byteclk_max = div64_u64((u64)ctx->req_pck_max * bitspp,
				ndl * 8);

		pll_max = byteclk_max * 4 * 4;
	}

	return dss_pll_calc_a(ctx->pll, clkin,
			pll_min, pll_max,
			dsi_vm_calc_pll_cb, ctx);
}