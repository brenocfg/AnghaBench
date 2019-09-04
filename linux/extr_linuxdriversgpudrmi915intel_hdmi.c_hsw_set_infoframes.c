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
struct intel_crtc_state {int /*<<< orphan*/  cpu_transcoder; } ;
struct drm_i915_private {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  dev; } ;
struct drm_connector_state {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  HSW_TVIDEO_DIP_CTL (int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int VIDEO_DIP_ENABLE_AVI_HSW ; 
 int VIDEO_DIP_ENABLE_GCP_HSW ; 
 int VIDEO_DIP_ENABLE_GMP_HSW ; 
 int VIDEO_DIP_ENABLE_SPD_HSW ; 
 int VIDEO_DIP_ENABLE_VSC_HSW ; 
 int VIDEO_DIP_ENABLE_VS_HSW ; 
 int /*<<< orphan*/  assert_hdmi_transcoder_func_disabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_hdmi_set_avi_infoframe (struct drm_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 scalar_t__ intel_hdmi_set_gcp_infoframe (struct drm_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_hdmi_set_hdmi_infoframe (struct drm_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_hdmi_set_spd_infoframe (struct drm_encoder*,struct intel_crtc_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hsw_set_infoframes(struct drm_encoder *encoder,
			       bool enable,
			       const struct intel_crtc_state *crtc_state,
			       const struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->dev);
	i915_reg_t reg = HSW_TVIDEO_DIP_CTL(crtc_state->cpu_transcoder);
	u32 val = I915_READ(reg);

	assert_hdmi_transcoder_func_disabled(dev_priv,
					     crtc_state->cpu_transcoder);

	val &= ~(VIDEO_DIP_ENABLE_VSC_HSW | VIDEO_DIP_ENABLE_AVI_HSW |
		 VIDEO_DIP_ENABLE_GCP_HSW | VIDEO_DIP_ENABLE_VS_HSW |
		 VIDEO_DIP_ENABLE_GMP_HSW | VIDEO_DIP_ENABLE_SPD_HSW);

	if (!enable) {
		I915_WRITE(reg, val);
		POSTING_READ(reg);
		return;
	}

	if (intel_hdmi_set_gcp_infoframe(encoder, crtc_state, conn_state))
		val |= VIDEO_DIP_ENABLE_GCP_HSW;

	I915_WRITE(reg, val);
	POSTING_READ(reg);

	intel_hdmi_set_avi_infoframe(encoder, crtc_state, conn_state);
	intel_hdmi_set_spd_infoframe(encoder, crtc_state);
	intel_hdmi_set_hdmi_infoframe(encoder, crtc_state, conn_state);
}