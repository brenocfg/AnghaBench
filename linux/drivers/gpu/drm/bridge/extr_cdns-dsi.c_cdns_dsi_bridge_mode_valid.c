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
struct drm_display_mode {int vtotal; int vsync_end; int vsync_start; int hdisplay; } ;
struct drm_bridge {int dummy; } ;
struct cdns_dsi_output {TYPE_1__* dev; } ;
struct cdns_dsi_input {int dummy; } ;
struct cdns_dsi_cfg {int dummy; } ;
struct cdns_dsi {struct cdns_dsi_output output; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_2__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int MODE_BAD ; 
 int MODE_H_ILLEGAL ; 
 int MODE_OK ; 
 int MODE_V_ILLEGAL ; 
 struct cdns_dsi_input* bridge_to_cdns_dsi_input (struct drm_bridge*) ; 
 int cdns_dsi_check_conf (struct cdns_dsi*,struct drm_display_mode const*,struct cdns_dsi_cfg*,int) ; 
 struct cdns_dsi* input_to_dsi (struct cdns_dsi_input*) ; 
 int mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drm_mode_status
cdns_dsi_bridge_mode_valid(struct drm_bridge *bridge,
			   const struct drm_display_mode *mode)
{
	struct cdns_dsi_input *input = bridge_to_cdns_dsi_input(bridge);
	struct cdns_dsi *dsi = input_to_dsi(input);
	struct cdns_dsi_output *output = &dsi->output;
	struct cdns_dsi_cfg dsi_cfg;
	int bpp, ret;

	/*
	 * VFP_DSI should be less than VFP_DPI and VFP_DSI should be at
	 * least 1.
	 */
	if (mode->vtotal - mode->vsync_end < 2)
		return MODE_V_ILLEGAL;

	/* VSA_DSI = VSA_DPI and must be at least 2. */
	if (mode->vsync_end - mode->vsync_start < 2)
		return MODE_V_ILLEGAL;

	/* HACT must be 32-bits aligned. */
	bpp = mipi_dsi_pixel_format_to_bpp(output->dev->format);
	if ((mode->hdisplay * bpp) % 32)
		return MODE_H_ILLEGAL;

	ret = cdns_dsi_check_conf(dsi, mode, &dsi_cfg, true);
	if (ret)
		return MODE_BAD;

	return MODE_OK;
}