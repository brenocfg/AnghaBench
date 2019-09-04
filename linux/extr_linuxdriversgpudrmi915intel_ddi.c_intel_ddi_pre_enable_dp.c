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
struct intel_digital_port {int /*<<< orphan*/  ddi_io_power_domain; } ;
struct intel_crtc_state {int /*<<< orphan*/  shared_dpll; int /*<<< orphan*/  lane_count; int /*<<< orphan*/  port_clock; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DP_MST ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_ICELAKE (struct drm_i915_private*) ; 
 int PORT_A ; 
 int PORT_E ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bxt_ddi_vswing_sequence (struct intel_encoder*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnl_ddi_vswing_sequence (struct intel_encoder*,int,int /*<<< orphan*/ ) ; 
 struct intel_digital_port* enc_to_dig_port (TYPE_1__*) ; 
 struct intel_dp* enc_to_intel_dp (TYPE_1__*) ; 
 int /*<<< orphan*/  icl_ddi_vswing_sequence (struct intel_encoder*,int,int /*<<< orphan*/ ) ; 
 int intel_crtc_has_type (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ddi_clk_select (struct intel_encoder*,int /*<<< orphan*/ ) ; 
 int intel_ddi_dp_level (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_ddi_enable_pipe_clock (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_ddi_init_dp_buf_reg (struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_ddi_main_link_aux_domain (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_set_link_params (struct intel_dp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_dp_sink_dpms (struct intel_dp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_start_link_train (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_stop_link_train (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_edp_panel_on (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_prepare_dp_ddi_buffers (struct intel_encoder*,struct intel_crtc_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_ddi_pre_enable_dp(struct intel_encoder *encoder,
				    const struct intel_crtc_state *crtc_state,
				    const struct drm_connector_state *conn_state)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = encoder->port;
	struct intel_digital_port *dig_port = enc_to_dig_port(&encoder->base);
	bool is_mst = intel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST);
	int level = intel_ddi_dp_level(intel_dp);

	WARN_ON(is_mst && (port == PORT_A || port == PORT_E));

	intel_display_power_get(dev_priv,
				intel_ddi_main_link_aux_domain(intel_dp));

	intel_dp_set_link_params(intel_dp, crtc_state->port_clock,
				 crtc_state->lane_count, is_mst);

	intel_edp_panel_on(intel_dp);

	intel_ddi_clk_select(encoder, crtc_state->shared_dpll);

	intel_display_power_get(dev_priv, dig_port->ddi_io_power_domain);

	if (IS_ICELAKE(dev_priv))
		icl_ddi_vswing_sequence(encoder, level, encoder->type);
	else if (IS_CANNONLAKE(dev_priv))
		cnl_ddi_vswing_sequence(encoder, level, encoder->type);
	else if (IS_GEN9_LP(dev_priv))
		bxt_ddi_vswing_sequence(encoder, level, encoder->type);
	else
		intel_prepare_dp_ddi_buffers(encoder, crtc_state);

	intel_ddi_init_dp_buf_reg(encoder);
	if (!is_mst)
		intel_dp_sink_dpms(intel_dp, DRM_MODE_DPMS_ON);
	intel_dp_start_link_train(intel_dp);
	if (port != PORT_A || INTEL_GEN(dev_priv) >= 9)
		intel_dp_stop_link_train(intel_dp);

	if (!is_mst)
		intel_ddi_enable_pipe_clock(crtc_state);
}