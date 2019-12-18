#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; scalar_t__ type; TYPE_5__ base; } ;
struct intel_dp {int /*<<< orphan*/  output_reg; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  crtc_clock; } ;
struct TYPE_7__ {TYPE_1__ adjusted_mode; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int has_audio; int limited_color_range; int lane_count; int port_clock; scalar_t__ pipe_bpp; int /*<<< orphan*/  dp_m_n; TYPE_2__ base; int /*<<< orphan*/  output_types; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; } ;
struct TYPE_8__ {scalar_t__ bpp; } ;
struct TYPE_9__ {TYPE_3__ edp; } ;
struct drm_i915_private {TYPE_4__ vbt; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int /*<<< orphan*/  DP_A ; 
 int DP_AUDIO_OUTPUT_ENABLE ; 
 int DP_COLOR_RANGE_16_235 ; 
 int DP_PLL_FREQ_162MHZ ; 
 int DP_PLL_FREQ_MASK ; 
 int DP_PORT_WIDTH_MASK ; 
 int DP_PORT_WIDTH_SHIFT ; 
 int DP_SYNC_HS_HIGH ; 
 int DP_SYNC_VS_HIGH ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,scalar_t__,scalar_t__) ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEL_OUTPUT_DP ; 
 scalar_t__ INTEL_OUTPUT_EDP ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 int PORT_A ; 
 int /*<<< orphan*/  TRANS_DP_CTL (int /*<<< orphan*/ ) ; 
 int TRANS_DP_HSYNC_ACTIVE_HIGH ; 
 int TRANS_DP_VSYNC_ACTIVE_HIGH ; 
 struct intel_dp* enc_to_intel_dp (TYPE_5__*) ; 
 int /*<<< orphan*/  intel_dotclock_calculate (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_dp_get_m_n (struct intel_crtc*,struct intel_crtc_state*) ; 
 scalar_t__ intel_dp_is_edp (struct intel_dp*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_dp_get_config(struct intel_encoder *encoder,
				struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	u32 tmp, flags = 0;
	enum port port = encoder->port;
	struct intel_crtc *crtc = to_intel_crtc(pipe_config->base.crtc);

	if (encoder->type == INTEL_OUTPUT_EDP)
		pipe_config->output_types |= BIT(INTEL_OUTPUT_EDP);
	else
		pipe_config->output_types |= BIT(INTEL_OUTPUT_DP);

	tmp = I915_READ(intel_dp->output_reg);

	pipe_config->has_audio = tmp & DP_AUDIO_OUTPUT_ENABLE && port != PORT_A;

	if (HAS_PCH_CPT(dev_priv) && port != PORT_A) {
		u32 trans_dp = I915_READ(TRANS_DP_CTL(crtc->pipe));

		if (trans_dp & TRANS_DP_HSYNC_ACTIVE_HIGH)
			flags |= DRM_MODE_FLAG_PHSYNC;
		else
			flags |= DRM_MODE_FLAG_NHSYNC;

		if (trans_dp & TRANS_DP_VSYNC_ACTIVE_HIGH)
			flags |= DRM_MODE_FLAG_PVSYNC;
		else
			flags |= DRM_MODE_FLAG_NVSYNC;
	} else {
		if (tmp & DP_SYNC_HS_HIGH)
			flags |= DRM_MODE_FLAG_PHSYNC;
		else
			flags |= DRM_MODE_FLAG_NHSYNC;

		if (tmp & DP_SYNC_VS_HIGH)
			flags |= DRM_MODE_FLAG_PVSYNC;
		else
			flags |= DRM_MODE_FLAG_NVSYNC;
	}

	pipe_config->base.adjusted_mode.flags |= flags;

	if (IS_G4X(dev_priv) && tmp & DP_COLOR_RANGE_16_235)
		pipe_config->limited_color_range = true;

	pipe_config->lane_count =
		((tmp & DP_PORT_WIDTH_MASK) >> DP_PORT_WIDTH_SHIFT) + 1;

	intel_dp_get_m_n(crtc, pipe_config);

	if (port == PORT_A) {
		if ((I915_READ(DP_A) & DP_PLL_FREQ_MASK) == DP_PLL_FREQ_162MHZ)
			pipe_config->port_clock = 162000;
		else
			pipe_config->port_clock = 270000;
	}

	pipe_config->base.adjusted_mode.crtc_clock =
		intel_dotclock_calculate(pipe_config->port_clock,
					 &pipe_config->dp_m_n);

	if (intel_dp_is_edp(intel_dp) && dev_priv->vbt.edp.bpp &&
	    pipe_config->pipe_bpp > dev_priv->vbt.edp.bpp) {
		/*
		 * This is a big fat ugly hack.
		 *
		 * Some machines in UEFI boot mode provide us a VBT that has 18
		 * bpp and 1.62 GHz link bandwidth for eDP, which for reasons
		 * unknown we fail to light up. Yet the same BIOS boots up with
		 * 24 bpp and 2.7 GHz link. Use the same bpp as the BIOS uses as
		 * max, not what it tells us to use.
		 *
		 * Note: This will still be broken if the eDP panel is not lit
		 * up by the BIOS, and thus we can't get the mode at module
		 * load.
		 */
		DRM_DEBUG_KMS("pipe has %d bpp for eDP panel, overriding BIOS-provided max %d bpp\n",
			      pipe_config->pipe_bpp, dev_priv->vbt.edp.bpp);
		dev_priv->vbt.edp.bpp = pipe_config->pipe_bpp;
	}
}