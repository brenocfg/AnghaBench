#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {scalar_t__ type; TYPE_1__ base; } ;
struct TYPE_12__ {int /*<<< orphan*/  drm; int /*<<< orphan*/  hdmi; int /*<<< orphan*/  spd; int /*<<< orphan*/  avi; int /*<<< orphan*/  enable; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_9__ {TYPE_2__ adjusted_mode; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int cpu_transcoder; int pipe_bpp; int has_hdmi_sink; int has_infoframe; int hdmi_scrambling; int hdmi_high_tmds_clock_ratio; int lane_count; TYPE_6__ infoframes; int /*<<< orphan*/  lane_lat_optim_mask; int /*<<< orphan*/  has_audio; int /*<<< orphan*/  output_types; TYPE_3__ base; } ;
struct intel_crtc {int dummy; } ;
struct TYPE_10__ {scalar_t__ bpp; } ;
struct TYPE_11__ {TYPE_4__ edp; } ;
struct drm_i915_private {TYPE_5__ vbt; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int DDI_PORT_WIDTH_MASK ; 
 int DDI_PORT_WIDTH_SHIFT ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,scalar_t__,scalar_t__) ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_AVI ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_DRM ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_SPD ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_VENDOR ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEL_OUTPUT_ANALOG ; 
 scalar_t__ INTEL_OUTPUT_DP ; 
 scalar_t__ INTEL_OUTPUT_DP_MST ; 
 scalar_t__ INTEL_OUTPUT_EDP ; 
 scalar_t__ INTEL_OUTPUT_HDMI ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
#define  TRANS_DDI_BPC_10 136 
#define  TRANS_DDI_BPC_12 135 
#define  TRANS_DDI_BPC_6 134 
#define  TRANS_DDI_BPC_8 133 
 int TRANS_DDI_BPC_MASK ; 
 int /*<<< orphan*/  TRANS_DDI_FUNC_CTL (int) ; 
 int TRANS_DDI_HDMI_SCRAMBLING ; 
 int TRANS_DDI_HIGH_TMDS_CHAR_RATE ; 
#define  TRANS_DDI_MODE_SELECT_DP_MST 132 
#define  TRANS_DDI_MODE_SELECT_DP_SST 131 
#define  TRANS_DDI_MODE_SELECT_DVI 130 
#define  TRANS_DDI_MODE_SELECT_FDI 129 
#define  TRANS_DDI_MODE_SELECT_HDMI 128 
 int TRANS_DDI_MODE_SELECT_MASK ; 
 int TRANS_DDI_PHSYNC ; 
 int TRANS_DDI_PVSYNC ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxt_ddi_phy_get_lane_lat_optim_mask (struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_ddi_clock_get (struct intel_encoder*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_ddi_compute_min_voltage_level (struct drm_i915_private*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_ddi_is_audio_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_dp_get_m_n (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_hdmi_infoframes_enabled (struct intel_encoder*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_hdmi_read_gcp_infoframe (struct intel_encoder*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_read_infoframe (struct intel_encoder*,struct intel_crtc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transcoder_is_dsi (int) ; 

void intel_ddi_get_config(struct intel_encoder *encoder,
			  struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(pipe_config->base.crtc);
	enum transcoder cpu_transcoder = pipe_config->cpu_transcoder;
	u32 temp, flags = 0;

	/* XXX: DSI transcoder paranoia */
	if (WARN_ON(transcoder_is_dsi(cpu_transcoder)))
		return;

	temp = I915_READ(TRANS_DDI_FUNC_CTL(cpu_transcoder));
	if (temp & TRANS_DDI_PHSYNC)
		flags |= DRM_MODE_FLAG_PHSYNC;
	else
		flags |= DRM_MODE_FLAG_NHSYNC;
	if (temp & TRANS_DDI_PVSYNC)
		flags |= DRM_MODE_FLAG_PVSYNC;
	else
		flags |= DRM_MODE_FLAG_NVSYNC;

	pipe_config->base.adjusted_mode.flags |= flags;

	switch (temp & TRANS_DDI_BPC_MASK) {
	case TRANS_DDI_BPC_6:
		pipe_config->pipe_bpp = 18;
		break;
	case TRANS_DDI_BPC_8:
		pipe_config->pipe_bpp = 24;
		break;
	case TRANS_DDI_BPC_10:
		pipe_config->pipe_bpp = 30;
		break;
	case TRANS_DDI_BPC_12:
		pipe_config->pipe_bpp = 36;
		break;
	default:
		break;
	}

	switch (temp & TRANS_DDI_MODE_SELECT_MASK) {
	case TRANS_DDI_MODE_SELECT_HDMI:
		pipe_config->has_hdmi_sink = true;

		pipe_config->infoframes.enable |=
			intel_hdmi_infoframes_enabled(encoder, pipe_config);

		if (pipe_config->infoframes.enable)
			pipe_config->has_infoframe = true;

		if (temp & TRANS_DDI_HDMI_SCRAMBLING)
			pipe_config->hdmi_scrambling = true;
		if (temp & TRANS_DDI_HIGH_TMDS_CHAR_RATE)
			pipe_config->hdmi_high_tmds_clock_ratio = true;
		/* fall through */
	case TRANS_DDI_MODE_SELECT_DVI:
		pipe_config->output_types |= BIT(INTEL_OUTPUT_HDMI);
		pipe_config->lane_count = 4;
		break;
	case TRANS_DDI_MODE_SELECT_FDI:
		pipe_config->output_types |= BIT(INTEL_OUTPUT_ANALOG);
		break;
	case TRANS_DDI_MODE_SELECT_DP_SST:
		if (encoder->type == INTEL_OUTPUT_EDP)
			pipe_config->output_types |= BIT(INTEL_OUTPUT_EDP);
		else
			pipe_config->output_types |= BIT(INTEL_OUTPUT_DP);
		pipe_config->lane_count =
			((temp & DDI_PORT_WIDTH_MASK) >> DDI_PORT_WIDTH_SHIFT) + 1;
		intel_dp_get_m_n(intel_crtc, pipe_config);
		break;
	case TRANS_DDI_MODE_SELECT_DP_MST:
		pipe_config->output_types |= BIT(INTEL_OUTPUT_DP_MST);
		pipe_config->lane_count =
			((temp & DDI_PORT_WIDTH_MASK) >> DDI_PORT_WIDTH_SHIFT) + 1;
		intel_dp_get_m_n(intel_crtc, pipe_config);
		break;
	default:
		break;
	}

	pipe_config->has_audio =
		intel_ddi_is_audio_enabled(dev_priv, cpu_transcoder);

	if (encoder->type == INTEL_OUTPUT_EDP && dev_priv->vbt.edp.bpp &&
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

	intel_ddi_clock_get(encoder, pipe_config);

	if (IS_GEN9_LP(dev_priv))
		pipe_config->lane_lat_optim_mask =
			bxt_ddi_phy_get_lane_lat_optim_mask(encoder);

	intel_ddi_compute_min_voltage_level(dev_priv, pipe_config);

	intel_hdmi_read_gcp_infoframe(encoder, pipe_config);

	intel_read_infoframe(encoder, pipe_config,
			     HDMI_INFOFRAME_TYPE_AVI,
			     &pipe_config->infoframes.avi);
	intel_read_infoframe(encoder, pipe_config,
			     HDMI_INFOFRAME_TYPE_SPD,
			     &pipe_config->infoframes.spd);
	intel_read_infoframe(encoder, pipe_config,
			     HDMI_INFOFRAME_TYPE_VENDOR,
			     &pipe_config->infoframes.hdmi);
	intel_read_infoframe(encoder, pipe_config,
			     HDMI_INFOFRAME_TYPE_DRM,
			     &pipe_config->infoframes.drm);
}