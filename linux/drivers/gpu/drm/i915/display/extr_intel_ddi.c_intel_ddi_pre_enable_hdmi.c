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
struct intel_hdmi {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_1__ base; } ;
struct intel_digital_port {int /*<<< orphan*/  (* set_infoframes ) (struct intel_encoder*,int /*<<< orphan*/ ,struct intel_crtc_state const*,struct drm_connector_state const*) ;int /*<<< orphan*/  ddi_io_power_domain; struct intel_hdmi hdmi; } ;
struct intel_crtc_state {int /*<<< orphan*/  has_infoframe; int /*<<< orphan*/  port_clock; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_ddi_vswing_sequence (struct intel_encoder*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnl_ddi_vswing_sequence (struct intel_encoder*,int,int /*<<< orphan*/ ) ; 
 struct intel_digital_port* enc_to_dig_port (TYPE_1__*) ; 
 int /*<<< orphan*/  icl_ddi_vswing_sequence (struct intel_encoder*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_disable_phy_clock_gating (struct intel_digital_port*) ; 
 int /*<<< orphan*/  icl_enable_phy_clock_gating (struct intel_digital_port*) ; 
 int /*<<< orphan*/  icl_program_mg_dp_mode (struct intel_digital_port*) ; 
 int /*<<< orphan*/  intel_ddi_clk_select (struct intel_encoder*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_ddi_enable_pipe_clock (struct intel_crtc_state const*) ; 
 int intel_ddi_hdmi_level (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_dual_mode_set_tmds_output (struct intel_hdmi*,int) ; 
 int /*<<< orphan*/  intel_prepare_hdmi_ddi_buffers (struct intel_encoder*,int) ; 
 int /*<<< orphan*/  skl_ddi_set_iboost (struct intel_encoder*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct intel_encoder*,int /*<<< orphan*/ ,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_ddi_pre_enable_hdmi(struct intel_encoder *encoder,
				      const struct intel_crtc_state *crtc_state,
				      const struct drm_connector_state *conn_state)
{
	struct intel_digital_port *intel_dig_port = enc_to_dig_port(&encoder->base);
	struct intel_hdmi *intel_hdmi = &intel_dig_port->hdmi;
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = encoder->port;
	int level = intel_ddi_hdmi_level(dev_priv, port);
	struct intel_digital_port *dig_port = enc_to_dig_port(&encoder->base);

	intel_dp_dual_mode_set_tmds_output(intel_hdmi, true);
	intel_ddi_clk_select(encoder, crtc_state);

	intel_display_power_get(dev_priv, dig_port->ddi_io_power_domain);

	icl_program_mg_dp_mode(dig_port);
	icl_disable_phy_clock_gating(dig_port);

	if (INTEL_GEN(dev_priv) >= 11)
		icl_ddi_vswing_sequence(encoder, crtc_state->port_clock,
					level, INTEL_OUTPUT_HDMI);
	else if (IS_CANNONLAKE(dev_priv))
		cnl_ddi_vswing_sequence(encoder, level, INTEL_OUTPUT_HDMI);
	else if (IS_GEN9_LP(dev_priv))
		bxt_ddi_vswing_sequence(encoder, level, INTEL_OUTPUT_HDMI);
	else
		intel_prepare_hdmi_ddi_buffers(encoder, level);

	icl_enable_phy_clock_gating(dig_port);

	if (IS_GEN9_BC(dev_priv))
		skl_ddi_set_iboost(encoder, level, INTEL_OUTPUT_HDMI);

	intel_ddi_enable_pipe_clock(crtc_state);

	intel_dig_port->set_infoframes(encoder,
				       crtc_state->has_infoframe,
				       crtc_state, conn_state);
}