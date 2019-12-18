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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int /*<<< orphan*/  port; TYPE_1__ base; } ;
struct intel_digital_port {scalar_t__ tc_mode; } ;
struct intel_crtc_state {int /*<<< orphan*/  lane_lat_optim_mask; int /*<<< orphan*/  lane_count; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ TC_PORT_TBT_ALT ; 
 int /*<<< orphan*/  bxt_ddi_phy_set_lane_optim_mask (struct intel_encoder*,int /*<<< orphan*/ ) ; 
 struct intel_digital_port* enc_to_dig_port (TYPE_1__*) ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_ddi_main_link_aux_domain (struct intel_digital_port*) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int intel_phy_is_tc (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_tc_port_get_link (struct intel_digital_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_tc_port_set_fia_lane_count (struct intel_digital_port*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_ddi_pre_pll_enable(struct intel_encoder *encoder,
			 const struct intel_crtc_state *crtc_state,
			 const struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_digital_port *dig_port = enc_to_dig_port(&encoder->base);
	enum phy phy = intel_port_to_phy(dev_priv, encoder->port);
	bool is_tc_port = intel_phy_is_tc(dev_priv, phy);

	if (is_tc_port)
		intel_tc_port_get_link(dig_port, crtc_state->lane_count);

	if (intel_crtc_has_dp_encoder(crtc_state) || is_tc_port)
		intel_display_power_get(dev_priv,
					intel_ddi_main_link_aux_domain(dig_port));

	if (is_tc_port && dig_port->tc_mode != TC_PORT_TBT_ALT)
		/*
		 * Program the lane count for static/dynamic connections on
		 * Type-C ports.  Skip this step for TBT.
		 */
		intel_tc_port_set_fia_lane_count(dig_port, crtc_state->lane_count);
	else if (IS_GEN9_LP(dev_priv))
		bxt_ddi_phy_set_lane_optim_mask(encoder,
						crtc_state->lane_lat_optim_mask);
}