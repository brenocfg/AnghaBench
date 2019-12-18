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
typedef  int u32 ;
struct mipi_phy_params {int dummy; } ;
struct dw_dsi {int lanes; int /*<<< orphan*/  format; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int clock; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
typedef  int /*<<< orphan*/  phy ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int MODE_BAD ; 
 int MODE_OK ; 
 int /*<<< orphan*/  drm_mode_vrefresh (struct drm_display_mode const*) ; 
 int dsi_calc_phy_rate (int,struct mipi_phy_params*) ; 
 struct dw_dsi* encoder_to_dsi (struct drm_encoder*) ; 
 int /*<<< orphan*/  memset (struct mipi_phy_params*,int /*<<< orphan*/ ,int) ; 
 int mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drm_mode_status dsi_encoder_phy_mode_valid(
					struct drm_encoder *encoder,
					const struct drm_display_mode *mode)
{
	struct dw_dsi *dsi = encoder_to_dsi(encoder);
	struct mipi_phy_params phy;
	u32 bpp = mipi_dsi_pixel_format_to_bpp(dsi->format);
	u32 req_kHz, act_kHz, lane_byte_clk_kHz;

	/* Calculate the lane byte clk using the adjusted mode clk */
	memset(&phy, 0, sizeof(phy));
	req_kHz = mode->clock * bpp / dsi->lanes;
	act_kHz = dsi_calc_phy_rate(req_kHz, &phy);
	lane_byte_clk_kHz = act_kHz / 8;

	DRM_DEBUG_DRIVER("Checking mode %ix%i-%i@%i clock: %i...",
			mode->hdisplay, mode->vdisplay, bpp,
			drm_mode_vrefresh(mode), mode->clock);

	/*
	 * Make sure the adjusted mode clock and the lane byte clk
	 * have a common denominator base frequency
	 */
	if (mode->clock/dsi->lanes == lane_byte_clk_kHz/3) {
		DRM_DEBUG_DRIVER("OK!\n");
		return MODE_OK;
	}

	DRM_DEBUG_DRIVER("BAD!\n");
	return MODE_BAD;
}