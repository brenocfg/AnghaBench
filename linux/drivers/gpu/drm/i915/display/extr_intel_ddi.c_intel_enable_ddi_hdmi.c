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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_2__ base; } ;
struct intel_digital_port {int saved_port_bits; } ;
struct intel_crtc_state {scalar_t__ has_audio; int /*<<< orphan*/  hdmi_scrambling; int /*<<< orphan*/  hdmi_high_tmds_clock_ratio; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {struct drm_connector* connector; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int /*<<< orphan*/  name; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int DDIE_TRAINING_OVERRIDE_ENABLE ; 
 int DDIE_TRAINING_OVERRIDE_VALUE ; 
 int /*<<< orphan*/  DDI_BUF_CTL (int) ; 
 int DDI_BUF_CTL_ENABLE ; 
 int DDI_TRAINING_OVERRIDE_ENABLE ; 
 int DDI_TRAINING_OVERRIDE_VALUE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 int PORT_E ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 struct intel_digital_port* enc_to_dig_port (TYPE_2__*) ; 
 int /*<<< orphan*/  gen9_chicken_trans_reg_by_port (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_audio_codec_enable (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_hdmi_handle_sink_scrambling (struct intel_encoder*,struct drm_connector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void intel_enable_ddi_hdmi(struct intel_encoder *encoder,
				  const struct intel_crtc_state *crtc_state,
				  const struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_digital_port *dig_port = enc_to_dig_port(&encoder->base);
	struct drm_connector *connector = conn_state->connector;
	enum port port = encoder->port;

	if (!intel_hdmi_handle_sink_scrambling(encoder, connector,
					       crtc_state->hdmi_high_tmds_clock_ratio,
					       crtc_state->hdmi_scrambling))
		DRM_ERROR("[CONNECTOR:%d:%s] Failed to configure sink scrambling/TMDS bit clock ratio\n",
			  connector->base.id, connector->name);

	/* Display WA #1143: skl,kbl,cfl */
	if (IS_GEN9_BC(dev_priv)) {
		/*
		 * For some reason these chicken bits have been
		 * stuffed into a transcoder register, event though
		 * the bits affect a specific DDI port rather than
		 * a specific transcoder.
		 */
		i915_reg_t reg = gen9_chicken_trans_reg_by_port(dev_priv, port);
		u32 val;

		val = I915_READ(reg);

		if (port == PORT_E)
			val |= DDIE_TRAINING_OVERRIDE_ENABLE |
				DDIE_TRAINING_OVERRIDE_VALUE;
		else
			val |= DDI_TRAINING_OVERRIDE_ENABLE |
				DDI_TRAINING_OVERRIDE_VALUE;

		I915_WRITE(reg, val);
		POSTING_READ(reg);

		udelay(1);

		if (port == PORT_E)
			val &= ~(DDIE_TRAINING_OVERRIDE_ENABLE |
				 DDIE_TRAINING_OVERRIDE_VALUE);
		else
			val &= ~(DDI_TRAINING_OVERRIDE_ENABLE |
				 DDI_TRAINING_OVERRIDE_VALUE);

		I915_WRITE(reg, val);
	}

	/* In HDMI/DVI mode, the port width, and swing/emphasis values
	 * are ignored so nothing special needs to be done besides
	 * enabling the port.
	 */
	I915_WRITE(DDI_BUF_CTL(port),
		   dig_port->saved_port_bits | DDI_BUF_CTL_ENABLE);

	if (crtc_state->has_audio)
		intel_audio_codec_enable(encoder, crtc_state, conn_state);
}