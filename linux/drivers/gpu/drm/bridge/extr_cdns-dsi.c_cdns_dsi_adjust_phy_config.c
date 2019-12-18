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
struct phy_configure_opts_mipi_dphy {unsigned long long hs_clk_rate; } ;
struct drm_display_mode {int clock; int crtc_clock; unsigned long htotal; unsigned long crtc_htotal; } ;
struct cdns_dsi_output {TYPE_1__* dev; } ;
struct cdns_dsi_cfg {unsigned long hbp; unsigned long htotal; scalar_t__ hfp; scalar_t__ hact; scalar_t__ hsa; } ;
struct cdns_dsi {struct cdns_dsi_output output; } ;
struct TYPE_2__ {unsigned int lanes; int mode_flags; } ;

/* Variables and functions */
 unsigned long DSI_HBP_FRAME_OVERHEAD ; 
 scalar_t__ DSI_HFP_FRAME_OVERHEAD ; 
 scalar_t__ DSI_HSA_FRAME_OVERHEAD ; 
 int EINVAL ; 
 int MIPI_DSI_MODE_VIDEO_SYNC_PULSE ; 
 scalar_t__ do_div (unsigned long long,unsigned int) ; 

__attribute__((used)) static int cdns_dsi_adjust_phy_config(struct cdns_dsi *dsi,
			      struct cdns_dsi_cfg *dsi_cfg,
			      struct phy_configure_opts_mipi_dphy *phy_cfg,
			      const struct drm_display_mode *mode,
			      bool mode_valid_check)
{
	struct cdns_dsi_output *output = &dsi->output;
	unsigned long long dlane_bps;
	unsigned long adj_dsi_htotal;
	unsigned long dsi_htotal;
	unsigned long dpi_htotal;
	unsigned long dpi_hz;
	unsigned int dsi_hfp_ext;
	unsigned int lanes = output->dev->lanes;

	dsi_htotal = dsi_cfg->hbp + DSI_HBP_FRAME_OVERHEAD;
	if (output->dev->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
		dsi_htotal += dsi_cfg->hsa + DSI_HSA_FRAME_OVERHEAD;

	dsi_htotal += dsi_cfg->hact;
	dsi_htotal += dsi_cfg->hfp + DSI_HFP_FRAME_OVERHEAD;

	/*
	 * Make sure DSI htotal is aligned on a lane boundary when calculating
	 * the expected data rate. This is done by extending HFP in case of
	 * misalignment.
	 */
	adj_dsi_htotal = dsi_htotal;
	if (dsi_htotal % lanes)
		adj_dsi_htotal += lanes - (dsi_htotal % lanes);

	dpi_hz = (mode_valid_check ? mode->clock : mode->crtc_clock) * 1000;
	dlane_bps = (unsigned long long)dpi_hz * adj_dsi_htotal;

	/* data rate in bytes/sec is not an integer, refuse the mode. */
	dpi_htotal = mode_valid_check ? mode->htotal : mode->crtc_htotal;
	if (do_div(dlane_bps, lanes * dpi_htotal))
		return -EINVAL;

	/* data rate was in bytes/sec, convert to bits/sec. */
	phy_cfg->hs_clk_rate = dlane_bps * 8;

	dsi_hfp_ext = adj_dsi_htotal - dsi_htotal;
	dsi_cfg->hfp += dsi_hfp_ext;
	dsi_cfg->htotal = dsi_htotal + dsi_hfp_ext;

	return 0;
}