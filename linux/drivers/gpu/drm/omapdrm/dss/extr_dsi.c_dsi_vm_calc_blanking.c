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
typedef  int u64 ;
struct videomode {int hactive; int hfront_porch; int hback_porch; int hsync_len; unsigned long pixelclock; int /*<<< orphan*/  vfront_porch; int /*<<< orphan*/  vactive; int /*<<< orphan*/  vback_porch; int /*<<< orphan*/  vsync_len; } ;
struct omap_dss_dsi_videomode_timings {unsigned long hsclk; int ndl; int bitspp; int hss; int hsa; int hse; int hbp; int hact; int hfp; scalar_t__ trans_mode; int hsa_blanking_mode; int hfp_blanking_mode; int hbp_blanking_mode; int window_sync; int /*<<< orphan*/  ddr_clk_always_on; scalar_t__ blanking_mode; int /*<<< orphan*/  vfp; int /*<<< orphan*/  vact; int /*<<< orphan*/  vbp; int /*<<< orphan*/  vsa; } ;
struct omap_dss_dsi_config {scalar_t__ trans_mode; int /*<<< orphan*/  ddr_clk_always_on; struct videomode* vm; int /*<<< orphan*/  pixel_format; } ;
struct dsi_data {int num_lanes_used; int line_buffer_size; } ;
struct TYPE_4__ {unsigned long pck; } ;
struct TYPE_3__ {int clkdco; } ;
struct dsi_clk_calc_ctx {unsigned long req_pck_min; unsigned long req_pck_max; unsigned long req_pck_nom; struct videomode vm; struct omap_dss_dsi_videomode_timings dsi_vm; TYPE_2__ dispc_cinfo; TYPE_1__ dsi_cinfo; struct omap_dss_dsi_config* config; struct dsi_data* dsi; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 scalar_t__ OMAP_DSS_DSI_BURST_MODE ; 
 scalar_t__ OMAP_DSS_DSI_PULSE_MODE ; 
 int div64_u64 (int,unsigned long) ; 
 int dsi_get_pixel_size (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memset (struct omap_dss_dsi_videomode_timings*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool dsi_vm_calc_blanking(struct dsi_clk_calc_ctx *ctx)
{
	struct dsi_data *dsi = ctx->dsi;
	const struct omap_dss_dsi_config *cfg = ctx->config;
	int bitspp = dsi_get_pixel_size(cfg->pixel_format);
	int ndl = dsi->num_lanes_used - 1;
	unsigned long hsclk = ctx->dsi_cinfo.clkdco / 4;
	unsigned long byteclk = hsclk / 4;

	unsigned long dispc_pck, req_pck_min, req_pck_nom, req_pck_max;
	int xres;
	int panel_htot, panel_hbl; /* pixels */
	int dispc_htot, dispc_hbl; /* pixels */
	int dsi_htot, dsi_hact, dsi_hbl, hss, hse; /* byteclks */
	int hfp, hsa, hbp;
	const struct videomode *req_vm;
	struct videomode *dispc_vm;
	struct omap_dss_dsi_videomode_timings *dsi_vm;
	u64 dsi_tput, dispc_tput;

	dsi_tput = (u64)byteclk * ndl * 8;

	req_vm = cfg->vm;
	req_pck_min = ctx->req_pck_min;
	req_pck_max = ctx->req_pck_max;
	req_pck_nom = ctx->req_pck_nom;

	dispc_pck = ctx->dispc_cinfo.pck;
	dispc_tput = (u64)dispc_pck * bitspp;

	xres = req_vm->hactive;

	panel_hbl = req_vm->hfront_porch + req_vm->hback_porch +
		    req_vm->hsync_len;
	panel_htot = xres + panel_hbl;

	dsi_hact = DIV_ROUND_UP(DIV_ROUND_UP(xres * bitspp, 8) + 6, ndl);

	/*
	 * When there are no line buffers, DISPC and DSI must have the
	 * same tput. Otherwise DISPC tput needs to be higher than DSI's.
	 */
	if (dsi->line_buffer_size < xres * bitspp / 8) {
		if (dispc_tput != dsi_tput)
			return false;
	} else {
		if (dispc_tput < dsi_tput)
			return false;
	}

	/* DSI tput must be over the min requirement */
	if (dsi_tput < (u64)bitspp * req_pck_min)
		return false;

	/* When non-burst mode, DSI tput must be below max requirement. */
	if (cfg->trans_mode != OMAP_DSS_DSI_BURST_MODE) {
		if (dsi_tput > (u64)bitspp * req_pck_max)
			return false;
	}

	hss = DIV_ROUND_UP(4, ndl);

	if (cfg->trans_mode == OMAP_DSS_DSI_PULSE_MODE) {
		if (ndl == 3 && req_vm->hsync_len == 0)
			hse = 1;
		else
			hse = DIV_ROUND_UP(4, ndl);
	} else {
		hse = 0;
	}

	/* DSI htot to match the panel's nominal pck */
	dsi_htot = div64_u64((u64)panel_htot * byteclk, req_pck_nom);

	/* fail if there would be no time for blanking */
	if (dsi_htot < hss + hse + dsi_hact)
		return false;

	/* total DSI blanking needed to achieve panel's TL */
	dsi_hbl = dsi_htot - dsi_hact;

	/* DISPC htot to match the DSI TL */
	dispc_htot = div64_u64((u64)dsi_htot * dispc_pck, byteclk);

	/* verify that the DSI and DISPC TLs are the same */
	if ((u64)dsi_htot * dispc_pck != (u64)dispc_htot * byteclk)
		return false;

	dispc_hbl = dispc_htot - xres;

	/* setup DSI videomode */

	dsi_vm = &ctx->dsi_vm;
	memset(dsi_vm, 0, sizeof(*dsi_vm));

	dsi_vm->hsclk = hsclk;

	dsi_vm->ndl = ndl;
	dsi_vm->bitspp = bitspp;

	if (cfg->trans_mode != OMAP_DSS_DSI_PULSE_MODE) {
		hsa = 0;
	} else if (ndl == 3 && req_vm->hsync_len == 0) {
		hsa = 0;
	} else {
		hsa = div64_u64((u64)req_vm->hsync_len * byteclk, req_pck_nom);
		hsa = max(hsa - hse, 1);
	}

	hbp = div64_u64((u64)req_vm->hback_porch * byteclk, req_pck_nom);
	hbp = max(hbp, 1);

	hfp = dsi_hbl - (hss + hsa + hse + hbp);
	if (hfp < 1) {
		int t;
		/* we need to take cycles from hbp */

		t = 1 - hfp;
		hbp = max(hbp - t, 1);
		hfp = dsi_hbl - (hss + hsa + hse + hbp);

		if (hfp < 1 && hsa > 0) {
			/* we need to take cycles from hsa */
			t = 1 - hfp;
			hsa = max(hsa - t, 1);
			hfp = dsi_hbl - (hss + hsa + hse + hbp);
		}
	}

	if (hfp < 1)
		return false;

	dsi_vm->hss = hss;
	dsi_vm->hsa = hsa;
	dsi_vm->hse = hse;
	dsi_vm->hbp = hbp;
	dsi_vm->hact = xres;
	dsi_vm->hfp = hfp;

	dsi_vm->vsa = req_vm->vsync_len;
	dsi_vm->vbp = req_vm->vback_porch;
	dsi_vm->vact = req_vm->vactive;
	dsi_vm->vfp = req_vm->vfront_porch;

	dsi_vm->trans_mode = cfg->trans_mode;

	dsi_vm->blanking_mode = 0;
	dsi_vm->hsa_blanking_mode = 1;
	dsi_vm->hfp_blanking_mode = 1;
	dsi_vm->hbp_blanking_mode = 1;

	dsi_vm->ddr_clk_always_on = cfg->ddr_clk_always_on;
	dsi_vm->window_sync = 4;

	/* setup DISPC videomode */

	dispc_vm = &ctx->vm;
	*dispc_vm = *req_vm;
	dispc_vm->pixelclock = dispc_pck;

	if (cfg->trans_mode == OMAP_DSS_DSI_PULSE_MODE) {
		hsa = div64_u64((u64)req_vm->hsync_len * dispc_pck,
				req_pck_nom);
		hsa = max(hsa, 1);
	} else {
		hsa = 1;
	}

	hbp = div64_u64((u64)req_vm->hback_porch * dispc_pck, req_pck_nom);
	hbp = max(hbp, 1);

	hfp = dispc_hbl - hsa - hbp;
	if (hfp < 1) {
		int t;
		/* we need to take cycles from hbp */

		t = 1 - hfp;
		hbp = max(hbp - t, 1);
		hfp = dispc_hbl - hsa - hbp;

		if (hfp < 1) {
			/* we need to take cycles from hsa */
			t = 1 - hfp;
			hsa = max(hsa - t, 1);
			hfp = dispc_hbl - hsa - hbp;
		}
	}

	if (hfp < 1)
		return false;

	dispc_vm->hfront_porch = hfp;
	dispc_vm->hsync_len = hsa;
	dispc_vm->hback_porch = hbp;

	return true;
}