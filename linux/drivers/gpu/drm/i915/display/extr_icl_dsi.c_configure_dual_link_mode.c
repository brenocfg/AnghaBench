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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_2__ base; } ;
struct intel_dsi {int pixel_overlap; scalar_t__ dual_link; } ;
struct drm_display_mode {int crtc_hdisplay; } ;
struct TYPE_3__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ DSI_DUAL_LINK_FRONT_BACK ; 
 int /*<<< orphan*/  DSS_CTL1 ; 
 int /*<<< orphan*/  DSS_CTL2 ; 
 int /*<<< orphan*/  DUAL_LINK_MODE_INTERLEAVE ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEFT_DL_BUF_TARGET_DEPTH (int) ; 
 int /*<<< orphan*/  LEFT_DL_BUF_TARGET_DEPTH_MASK ; 
 int MAX_DL_BUFFER_TARGET_DEPTH ; 
 int /*<<< orphan*/  OVERLAP_PIXELS (int) ; 
 int /*<<< orphan*/  OVERLAP_PIXELS_MASK ; 
 int /*<<< orphan*/  RIGHT_DL_BUF_TARGET_DEPTH (int) ; 
 int /*<<< orphan*/  RIGHT_DL_BUF_TARGET_DEPTH_MASK ; 
 int /*<<< orphan*/  SPLITTER_ENABLE ; 
 struct intel_dsi* enc_to_intel_dsi (TYPE_2__*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void configure_dual_link_mode(struct intel_encoder *encoder,
				     const struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_dsi *intel_dsi = enc_to_intel_dsi(&encoder->base);
	u32 dss_ctl1;

	dss_ctl1 = I915_READ(DSS_CTL1);
	dss_ctl1 |= SPLITTER_ENABLE;
	dss_ctl1 &= ~OVERLAP_PIXELS_MASK;
	dss_ctl1 |= OVERLAP_PIXELS(intel_dsi->pixel_overlap);

	if (intel_dsi->dual_link == DSI_DUAL_LINK_FRONT_BACK) {
		const struct drm_display_mode *adjusted_mode =
					&pipe_config->base.adjusted_mode;
		u32 dss_ctl2;
		u16 hactive = adjusted_mode->crtc_hdisplay;
		u16 dl_buffer_depth;

		dss_ctl1 &= ~DUAL_LINK_MODE_INTERLEAVE;
		dl_buffer_depth = hactive / 2 + intel_dsi->pixel_overlap;

		if (dl_buffer_depth > MAX_DL_BUFFER_TARGET_DEPTH)
			DRM_ERROR("DL buffer depth exceed max value\n");

		dss_ctl1 &= ~LEFT_DL_BUF_TARGET_DEPTH_MASK;
		dss_ctl1 |= LEFT_DL_BUF_TARGET_DEPTH(dl_buffer_depth);
		dss_ctl2 = I915_READ(DSS_CTL2);
		dss_ctl2 &= ~RIGHT_DL_BUF_TARGET_DEPTH_MASK;
		dss_ctl2 |= RIGHT_DL_BUF_TARGET_DEPTH(dl_buffer_depth);
		I915_WRITE(DSS_CTL2, dss_ctl2);
	} else {
		/* Interleave */
		dss_ctl1 |= DUAL_LINK_MODE_INTERLEAVE;
	}

	I915_WRITE(DSS_CTL1, dss_ctl1);
}