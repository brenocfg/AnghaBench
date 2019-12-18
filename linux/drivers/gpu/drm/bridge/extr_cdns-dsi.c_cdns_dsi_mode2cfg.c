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
struct drm_display_mode {unsigned int htotal; unsigned int hsync_end; unsigned int hsync_start; unsigned int crtc_htotal; unsigned int crtc_hsync_end; unsigned int crtc_hsync_start; unsigned int hdisplay; unsigned int crtc_hdisplay; } ;
struct cdns_dsi_output {TYPE_1__* dev; } ;
struct cdns_dsi_cfg {void* hfp; void* hact; void* hsa; void* hbp; } ;
struct cdns_dsi {struct cdns_dsi_output output; } ;
struct TYPE_2__ {int mode_flags; int lanes; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_HBP_FRAME_OVERHEAD ; 
 int /*<<< orphan*/  DSI_HFP_FRAME_OVERHEAD ; 
 int /*<<< orphan*/  DSI_HSA_FRAME_OVERHEAD ; 
 int MIPI_DSI_MODE_VIDEO_SYNC_PULSE ; 
 void* dpi_to_dsi_timing (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cdns_dsi_cfg*,int /*<<< orphan*/ ,int) ; 
 int mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 
 unsigned int mode_to_dpi_hfp (struct drm_display_mode const*,int) ; 

__attribute__((used)) static int cdns_dsi_mode2cfg(struct cdns_dsi *dsi,
			     const struct drm_display_mode *mode,
			     struct cdns_dsi_cfg *dsi_cfg,
			     bool mode_valid_check)
{
	struct cdns_dsi_output *output = &dsi->output;
	unsigned int tmp;
	bool sync_pulse = false;
	int bpp, nlanes;

	memset(dsi_cfg, 0, sizeof(*dsi_cfg));

	if (output->dev->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
		sync_pulse = true;

	bpp = mipi_dsi_pixel_format_to_bpp(output->dev->format);
	nlanes = output->dev->lanes;

	if (mode_valid_check)
		tmp = mode->htotal -
		      (sync_pulse ? mode->hsync_end : mode->hsync_start);
	else
		tmp = mode->crtc_htotal -
		      (sync_pulse ?
		       mode->crtc_hsync_end : mode->crtc_hsync_start);

	dsi_cfg->hbp = dpi_to_dsi_timing(tmp, bpp, DSI_HBP_FRAME_OVERHEAD);

	if (sync_pulse) {
		if (mode_valid_check)
			tmp = mode->hsync_end - mode->hsync_start;
		else
			tmp = mode->crtc_hsync_end - mode->crtc_hsync_start;

		dsi_cfg->hsa = dpi_to_dsi_timing(tmp, bpp,
						 DSI_HSA_FRAME_OVERHEAD);
	}

	dsi_cfg->hact = dpi_to_dsi_timing(mode_valid_check ?
					  mode->hdisplay : mode->crtc_hdisplay,
					  bpp, 0);
	dsi_cfg->hfp = dpi_to_dsi_timing(mode_to_dpi_hfp(mode, mode_valid_check),
					 bpp, DSI_HFP_FRAME_OVERHEAD);

	return 0;
}