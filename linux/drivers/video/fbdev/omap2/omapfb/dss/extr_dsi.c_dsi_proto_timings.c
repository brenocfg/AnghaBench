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
typedef  int u32 ;
struct platform_device {int dummy; } ;
struct omap_video_timings {int x_res; int y_res; } ;
struct TYPE_2__ {int hsa; int hfp; int hbp; int vsa; int vfp; int vbp; int window_sync; scalar_t__ trans_mode; } ;
struct dsi_data {int num_lanes_used; scalar_t__ mode; TYPE_1__ vm_timings; int /*<<< orphan*/  pix_fmt; struct omap_video_timings timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DSI_CLK_TIMING ; 
 int /*<<< orphan*/  DSI_DSIPHY_CFG0 ; 
 int /*<<< orphan*/  DSI_DSIPHY_CFG1 ; 
 int /*<<< orphan*/  DSI_DSIPHY_CFG2 ; 
 int /*<<< orphan*/  DSI_VM_TIMING1 ; 
 int /*<<< orphan*/  DSI_VM_TIMING2 ; 
 int /*<<< orphan*/  DSI_VM_TIMING3 ; 
 int /*<<< orphan*/  DSI_VM_TIMING7 ; 
 int /*<<< orphan*/  DSSDBG (char*,int,int,...) ; 
 int FLD_GET (int,int,int) ; 
 int FLD_MOD (int,int,int,int) ; 
 int FLD_VAL (unsigned int,int,int) ; 
 scalar_t__ OMAP_DSS_DSI_PULSE_MODE ; 
 scalar_t__ OMAP_DSS_DSI_VIDEO_MODE ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int dsi_get_pixel_size (int /*<<< orphan*/ ) ; 
 int dsi_read_reg (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write_reg (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int ns2ddr (struct platform_device*,int) ; 

__attribute__((used)) static void dsi_proto_timings(struct platform_device *dsidev)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	unsigned tlpx, tclk_zero, tclk_prepare, tclk_trail;
	unsigned tclk_pre, tclk_post;
	unsigned ths_prepare, ths_prepare_ths_zero, ths_zero;
	unsigned ths_trail, ths_exit;
	unsigned ddr_clk_pre, ddr_clk_post;
	unsigned enter_hs_mode_lat, exit_hs_mode_lat;
	unsigned ths_eot;
	int ndl = dsi->num_lanes_used - 1;
	u32 r;

	r = dsi_read_reg(dsidev, DSI_DSIPHY_CFG0);
	ths_prepare = FLD_GET(r, 31, 24);
	ths_prepare_ths_zero = FLD_GET(r, 23, 16);
	ths_zero = ths_prepare_ths_zero - ths_prepare;
	ths_trail = FLD_GET(r, 15, 8);
	ths_exit = FLD_GET(r, 7, 0);

	r = dsi_read_reg(dsidev, DSI_DSIPHY_CFG1);
	tlpx = FLD_GET(r, 20, 16) * 2;
	tclk_trail = FLD_GET(r, 15, 8);
	tclk_zero = FLD_GET(r, 7, 0);

	r = dsi_read_reg(dsidev, DSI_DSIPHY_CFG2);
	tclk_prepare = FLD_GET(r, 7, 0);

	/* min 8*UI */
	tclk_pre = 20;
	/* min 60ns + 52*UI */
	tclk_post = ns2ddr(dsidev, 60) + 26;

	ths_eot = DIV_ROUND_UP(4, ndl);

	ddr_clk_pre = DIV_ROUND_UP(tclk_pre + tlpx + tclk_zero + tclk_prepare,
			4);
	ddr_clk_post = DIV_ROUND_UP(tclk_post + ths_trail, 4) + ths_eot;

	BUG_ON(ddr_clk_pre == 0 || ddr_clk_pre > 255);
	BUG_ON(ddr_clk_post == 0 || ddr_clk_post > 255);

	r = dsi_read_reg(dsidev, DSI_CLK_TIMING);
	r = FLD_MOD(r, ddr_clk_pre, 15, 8);
	r = FLD_MOD(r, ddr_clk_post, 7, 0);
	dsi_write_reg(dsidev, DSI_CLK_TIMING, r);

	DSSDBG("ddr_clk_pre %u, ddr_clk_post %u\n",
			ddr_clk_pre,
			ddr_clk_post);

	enter_hs_mode_lat = 1 + DIV_ROUND_UP(tlpx, 4) +
		DIV_ROUND_UP(ths_prepare, 4) +
		DIV_ROUND_UP(ths_zero + 3, 4);

	exit_hs_mode_lat = DIV_ROUND_UP(ths_trail + ths_exit, 4) + 1 + ths_eot;

	r = FLD_VAL(enter_hs_mode_lat, 31, 16) |
		FLD_VAL(exit_hs_mode_lat, 15, 0);
	dsi_write_reg(dsidev, DSI_VM_TIMING7, r);

	DSSDBG("enter_hs_mode_lat %u, exit_hs_mode_lat %u\n",
			enter_hs_mode_lat, exit_hs_mode_lat);

	 if (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) {
		/* TODO: Implement a video mode check_timings function */
		int hsa = dsi->vm_timings.hsa;
		int hfp = dsi->vm_timings.hfp;
		int hbp = dsi->vm_timings.hbp;
		int vsa = dsi->vm_timings.vsa;
		int vfp = dsi->vm_timings.vfp;
		int vbp = dsi->vm_timings.vbp;
		int window_sync = dsi->vm_timings.window_sync;
		bool hsync_end;
		struct omap_video_timings *timings = &dsi->timings;
		int bpp = dsi_get_pixel_size(dsi->pix_fmt);
		int tl, t_he, width_bytes;

		hsync_end = dsi->vm_timings.trans_mode == OMAP_DSS_DSI_PULSE_MODE;
		t_he = hsync_end ?
			((hsa == 0 && ndl == 3) ? 1 : DIV_ROUND_UP(4, ndl)) : 0;

		width_bytes = DIV_ROUND_UP(timings->x_res * bpp, 8);

		/* TL = t_HS + HSA + t_HE + HFP + ceil((WC + 6) / NDL) + HBP */
		tl = DIV_ROUND_UP(4, ndl) + (hsync_end ? hsa : 0) + t_he + hfp +
			DIV_ROUND_UP(width_bytes + 6, ndl) + hbp;

		DSSDBG("HBP: %d, HFP: %d, HSA: %d, TL: %d TXBYTECLKHS\n", hbp,
			hfp, hsync_end ? hsa : 0, tl);
		DSSDBG("VBP: %d, VFP: %d, VSA: %d, VACT: %d lines\n", vbp, vfp,
			vsa, timings->y_res);

		r = dsi_read_reg(dsidev, DSI_VM_TIMING1);
		r = FLD_MOD(r, hbp, 11, 0);	/* HBP */
		r = FLD_MOD(r, hfp, 23, 12);	/* HFP */
		r = FLD_MOD(r, hsync_end ? hsa : 0, 31, 24);	/* HSA */
		dsi_write_reg(dsidev, DSI_VM_TIMING1, r);

		r = dsi_read_reg(dsidev, DSI_VM_TIMING2);
		r = FLD_MOD(r, vbp, 7, 0);	/* VBP */
		r = FLD_MOD(r, vfp, 15, 8);	/* VFP */
		r = FLD_MOD(r, vsa, 23, 16);	/* VSA */
		r = FLD_MOD(r, window_sync, 27, 24);	/* WINDOW_SYNC */
		dsi_write_reg(dsidev, DSI_VM_TIMING2, r);

		r = dsi_read_reg(dsidev, DSI_VM_TIMING3);
		r = FLD_MOD(r, timings->y_res, 14, 0);	/* VACT */
		r = FLD_MOD(r, tl, 31, 16);		/* TL */
		dsi_write_reg(dsidev, DSI_VM_TIMING3, r);
	}
}