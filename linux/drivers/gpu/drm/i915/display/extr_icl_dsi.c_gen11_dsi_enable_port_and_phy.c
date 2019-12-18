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
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  gen11_dsi_config_phy_lanes_sequence (struct intel_encoder*) ; 
 int /*<<< orphan*/  gen11_dsi_configure_transcoder (struct intel_encoder*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  gen11_dsi_enable_ddi_buffer (struct intel_encoder*) ; 
 int /*<<< orphan*/  gen11_dsi_gate_clocks (struct intel_encoder*) ; 
 int /*<<< orphan*/  gen11_dsi_power_up_lanes (struct intel_encoder*) ; 
 int /*<<< orphan*/  gen11_dsi_setup_dphy_timings (struct intel_encoder*) ; 
 int /*<<< orphan*/  gen11_dsi_setup_timeouts (struct intel_encoder*) ; 
 int /*<<< orphan*/  gen11_dsi_voltage_swing_program_seq (struct intel_encoder*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen11_dsi_enable_port_and_phy(struct intel_encoder *encoder,
			      const struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);

	/* step 4a: power up all lanes of the DDI used by DSI */
	gen11_dsi_power_up_lanes(encoder);

	/* step 4b: configure lane sequencing of the Combo-PHY transmitters */
	gen11_dsi_config_phy_lanes_sequence(encoder);

	/* step 4c: configure voltage swing and skew */
	gen11_dsi_voltage_swing_program_seq(encoder);

	/* enable DDI buffer */
	gen11_dsi_enable_ddi_buffer(encoder);

	/* setup D-PHY timings */
	gen11_dsi_setup_dphy_timings(encoder);

	/* step 4h: setup DSI protocol timeouts */
	gen11_dsi_setup_timeouts(encoder);

	/* Step (4h, 4i, 4j, 4k): Configure transcoder */
	gen11_dsi_configure_transcoder(encoder, pipe_config);

	/* Step 4l: Gate DDI clocks */
	if (IS_GEN(dev_priv, 11))
		gen11_dsi_gate_clocks(encoder);
}