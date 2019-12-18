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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_2__ base; int /*<<< orphan*/  port; } ;
struct intel_digital_port {int /*<<< orphan*/  ddi_io_power_domain; } ;
struct TYPE_3__ {scalar_t__ compression_enable; } ;
struct intel_crtc_state {TYPE_1__ dsc_params; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_OUTPUT_DP_MST ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 struct intel_digital_port* enc_to_dig_port (TYPE_2__*) ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ddi_main_link_aux_domain (struct intel_digital_port*) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dsc_power_domain (struct intel_crtc_state*) ; 
 scalar_t__ intel_phy_is_tc (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_ddi_get_power_domains(struct intel_encoder *encoder,
					struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_digital_port *dig_port;
	enum phy phy = intel_port_to_phy(dev_priv, encoder->port);

	/*
	 * TODO: Add support for MST encoders. Atm, the following should never
	 * happen since fake-MST encoders don't set their get_power_domains()
	 * hook.
	 */
	if (WARN_ON(intel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST)))
		return;

	dig_port = enc_to_dig_port(&encoder->base);
	intel_display_power_get(dev_priv, dig_port->ddi_io_power_domain);

	/*
	 * AUX power is only needed for (e)DP mode, and for HDMI mode on TC
	 * ports.
	 */
	if (intel_crtc_has_dp_encoder(crtc_state) ||
	    intel_phy_is_tc(dev_priv, phy))
		intel_display_power_get(dev_priv,
					intel_ddi_main_link_aux_domain(dig_port));

	/*
	 * VDSC power is needed when DSC is enabled
	 */
	if (crtc_state->dsc_params.compression_enable)
		intel_display_power_get(dev_priv,
					intel_dsc_power_domain(crtc_state));
}