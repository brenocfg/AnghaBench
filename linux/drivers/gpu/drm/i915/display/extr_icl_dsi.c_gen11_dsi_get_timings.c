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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dsi {scalar_t__ dual_link; scalar_t__ operation_mode; scalar_t__ pixel_overlap; } ;
struct drm_display_mode {int crtc_hdisplay; int crtc_htotal; int crtc_hblank_start; int crtc_hblank_end; int crtc_hsync_start; int crtc_hsync_end; int /*<<< orphan*/  crtc_vtotal; int /*<<< orphan*/  crtc_vblank_end; int /*<<< orphan*/  crtc_vdisplay; int /*<<< orphan*/  crtc_vblank_start; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ DSI_DUAL_LINK_FRONT_BACK ; 
 scalar_t__ INTEL_DSI_VIDEO_MODE ; 
 struct intel_dsi* enc_to_intel_dsi (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gen11_dsi_get_timings(struct intel_encoder *encoder,
				  struct intel_crtc_state *pipe_config)
{
	struct intel_dsi *intel_dsi = enc_to_intel_dsi(&encoder->base);
	struct drm_display_mode *adjusted_mode =
					&pipe_config->base.adjusted_mode;

	if (intel_dsi->dual_link) {
		adjusted_mode->crtc_hdisplay *= 2;
		if (intel_dsi->dual_link == DSI_DUAL_LINK_FRONT_BACK)
			adjusted_mode->crtc_hdisplay -=
						intel_dsi->pixel_overlap;
		adjusted_mode->crtc_htotal *= 2;
	}
	adjusted_mode->crtc_hblank_start = adjusted_mode->crtc_hdisplay;
	adjusted_mode->crtc_hblank_end = adjusted_mode->crtc_htotal;

	if (intel_dsi->operation_mode == INTEL_DSI_VIDEO_MODE) {
		if (intel_dsi->dual_link) {
			adjusted_mode->crtc_hsync_start *= 2;
			adjusted_mode->crtc_hsync_end *= 2;
		}
	}
	adjusted_mode->crtc_vblank_start = adjusted_mode->crtc_vdisplay;
	adjusted_mode->crtc_vblank_end = adjusted_mode->crtc_vtotal;
}