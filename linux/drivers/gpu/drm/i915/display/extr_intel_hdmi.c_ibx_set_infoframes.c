#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_hdmi {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int /*<<< orphan*/  port; TYPE_3__ base; } ;
struct intel_digital_port {struct intel_hdmi hdmi; } ;
struct TYPE_5__ {int /*<<< orphan*/  hdmi; int /*<<< orphan*/  spd; int /*<<< orphan*/  avi; } ;
struct TYPE_4__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_2__ infoframes; TYPE_1__ base; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_AVI ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_SPD ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_VENDOR ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVIDEO_DIP_CTL (int /*<<< orphan*/ ) ; 
 int VIDEO_DIP_ENABLE ; 
 int VIDEO_DIP_ENABLE_AVI ; 
 int VIDEO_DIP_ENABLE_GAMUT ; 
 int VIDEO_DIP_ENABLE_GCP ; 
 int VIDEO_DIP_ENABLE_SPD ; 
 int VIDEO_DIP_ENABLE_VENDOR ; 
 int VIDEO_DIP_FREQ_VSYNC ; 
 int VIDEO_DIP_PORT (int /*<<< orphan*/ ) ; 
 int VIDEO_DIP_PORT_MASK ; 
 int VIDEO_DIP_SELECT_AVI ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  assert_hdmi_port_disabled (struct intel_hdmi*) ; 
 struct intel_digital_port* enc_to_dig_port (TYPE_3__*) ; 
 scalar_t__ intel_hdmi_set_gcp_infoframe (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_write_infoframe (struct intel_encoder*,struct intel_crtc_state const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibx_set_infoframes(struct intel_encoder *encoder,
			       bool enable,
			       const struct intel_crtc_state *crtc_state,
			       const struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc_state->base.crtc);
	struct intel_digital_port *intel_dig_port = enc_to_dig_port(&encoder->base);
	struct intel_hdmi *intel_hdmi = &intel_dig_port->hdmi;
	i915_reg_t reg = TVIDEO_DIP_CTL(intel_crtc->pipe);
	u32 val = I915_READ(reg);
	u32 port = VIDEO_DIP_PORT(encoder->port);

	assert_hdmi_port_disabled(intel_hdmi);

	/* See the big comment in g4x_set_infoframes() */
	val |= VIDEO_DIP_SELECT_AVI | VIDEO_DIP_FREQ_VSYNC;

	if (!enable) {
		if (!(val & VIDEO_DIP_ENABLE))
			return;
		val &= ~(VIDEO_DIP_ENABLE | VIDEO_DIP_ENABLE_AVI |
			 VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
			 VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);
		I915_WRITE(reg, val);
		POSTING_READ(reg);
		return;
	}

	if (port != (val & VIDEO_DIP_PORT_MASK)) {
		WARN(val & VIDEO_DIP_ENABLE,
		     "DIP already enabled on port %c\n",
		     (val & VIDEO_DIP_PORT_MASK) >> 29);
		val &= ~VIDEO_DIP_PORT_MASK;
		val |= port;
	}

	val |= VIDEO_DIP_ENABLE;
	val &= ~(VIDEO_DIP_ENABLE_AVI |
		 VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
		 VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);

	if (intel_hdmi_set_gcp_infoframe(encoder, crtc_state, conn_state))
		val |= VIDEO_DIP_ENABLE_GCP;

	I915_WRITE(reg, val);
	POSTING_READ(reg);

	intel_write_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_AVI,
			      &crtc_state->infoframes.avi);
	intel_write_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_SPD,
			      &crtc_state->infoframes.spd);
	intel_write_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_VENDOR,
			      &crtc_state->infoframes.hdmi);
}