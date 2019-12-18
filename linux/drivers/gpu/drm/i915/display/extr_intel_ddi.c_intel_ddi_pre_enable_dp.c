#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; int /*<<< orphan*/  type; TYPE_1__ base; } ;
struct intel_dp {int dummy; } ;
struct intel_digital_port {scalar_t__ tc_mode; int saved_port_bits; int /*<<< orphan*/  ddi_io_power_domain; } ;
struct intel_crtc_state {int /*<<< orphan*/  lane_count; int /*<<< orphan*/  port_clock; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int DDI_BUF_PORT_REVERSAL ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DP_MST ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int PORT_A ; 
 int PORT_E ; 
 scalar_t__ TC_PORT_TBT_ALT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bxt_ddi_vswing_sequence (struct intel_encoder*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnl_ddi_vswing_sequence (struct intel_encoder*,int,int /*<<< orphan*/ ) ; 
 struct intel_digital_port* enc_to_dig_port (TYPE_1__*) ; 
 struct intel_dp* enc_to_intel_dp (TYPE_1__*) ; 
 int /*<<< orphan*/  icl_ddi_vswing_sequence (struct intel_encoder*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_disable_phy_clock_gating (struct intel_digital_port*) ; 
 int /*<<< orphan*/  icl_enable_phy_clock_gating (struct intel_digital_port*) ; 
 int /*<<< orphan*/  icl_program_mg_dp_mode (struct intel_digital_port*) ; 
 int /*<<< orphan*/  intel_combo_phy_power_up_lanes (struct drm_i915_private*,int,int,int /*<<< orphan*/ ,int) ; 
 int intel_crtc_has_type (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ddi_clk_select (struct intel_encoder*,struct intel_crtc_state const*) ; 
 int intel_ddi_dp_level (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_ddi_enable_fec (struct intel_encoder*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_ddi_enable_pipe_clock (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_ddi_init_dp_buf_reg (struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_set_link_params (struct intel_dp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_dp_sink_dpms (struct intel_dp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_sink_set_decompression_state (struct intel_dp*,struct intel_crtc_state const*,int) ; 
 int /*<<< orphan*/  intel_dp_sink_set_fec_ready (struct intel_dp*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_dp_start_link_train (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_stop_link_train (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dsc_enable (struct intel_encoder*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_edp_panel_on (struct intel_dp*) ; 
 scalar_t__ intel_phy_is_combo (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_phy_is_tc (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_prepare_dp_ddi_buffers (struct intel_encoder*,struct intel_crtc_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_ddi_pre_enable_dp(struct intel_encoder *encoder,
				    const struct intel_crtc_state *crtc_state,
				    const struct drm_connector_state *conn_state)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = encoder->port;
	enum phy phy = intel_port_to_phy(dev_priv, port);
	struct intel_digital_port *dig_port = enc_to_dig_port(&encoder->base);
	bool is_mst = intel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST);
	int level = intel_ddi_dp_level(intel_dp);

	WARN_ON(is_mst && (port == PORT_A || port == PORT_E));

	intel_dp_set_link_params(intel_dp, crtc_state->port_clock,
				 crtc_state->lane_count, is_mst);

	intel_edp_panel_on(intel_dp);

	intel_ddi_clk_select(encoder, crtc_state);

	if (!intel_phy_is_tc(dev_priv, phy) ||
	    dig_port->tc_mode != TC_PORT_TBT_ALT)
		intel_display_power_get(dev_priv,
					dig_port->ddi_io_power_domain);

	icl_program_mg_dp_mode(dig_port);
	icl_disable_phy_clock_gating(dig_port);

	if (INTEL_GEN(dev_priv) >= 11)
		icl_ddi_vswing_sequence(encoder, crtc_state->port_clock,
					level, encoder->type);
	else if (IS_CANNONLAKE(dev_priv))
		cnl_ddi_vswing_sequence(encoder, level, encoder->type);
	else if (IS_GEN9_LP(dev_priv))
		bxt_ddi_vswing_sequence(encoder, level, encoder->type);
	else
		intel_prepare_dp_ddi_buffers(encoder, crtc_state);

	if (intel_phy_is_combo(dev_priv, phy)) {
		bool lane_reversal =
			dig_port->saved_port_bits & DDI_BUF_PORT_REVERSAL;

		intel_combo_phy_power_up_lanes(dev_priv, phy, false,
					       crtc_state->lane_count,
					       lane_reversal);
	}

	intel_ddi_init_dp_buf_reg(encoder);
	if (!is_mst)
		intel_dp_sink_dpms(intel_dp, DRM_MODE_DPMS_ON);
	intel_dp_sink_set_decompression_state(intel_dp, crtc_state,
					      true);
	intel_dp_sink_set_fec_ready(intel_dp, crtc_state);
	intel_dp_start_link_train(intel_dp);
	if (port != PORT_A || INTEL_GEN(dev_priv) >= 9)
		intel_dp_stop_link_train(intel_dp);

	intel_ddi_enable_fec(encoder, crtc_state);

	icl_enable_phy_clock_gating(dig_port);

	if (!is_mst)
		intel_ddi_enable_pipe_clock(crtc_state);

	intel_dsc_enable(encoder, crtc_state);
}