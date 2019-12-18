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
struct intel_encoder {TYPE_1__ base; } ;
struct intel_digital_port {int /*<<< orphan*/  ddi_io_power_domain; int /*<<< orphan*/  (* set_infoframes ) (struct intel_encoder*,int,struct intel_crtc_state const*,struct drm_connector_state const*) ;struct intel_hdmi hdmi; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 struct intel_digital_port* enc_to_dig_port (TYPE_1__*) ; 
 int /*<<< orphan*/  intel_ddi_clk_disable (struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_ddi_disable_pipe_clock (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_disable_ddi_buf (struct intel_encoder*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_display_power_put_unchecked (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_dual_mode_set_tmds_output (struct intel_hdmi*,int) ; 
 int /*<<< orphan*/  stub1 (struct intel_encoder*,int,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_ddi_post_disable_hdmi(struct intel_encoder *encoder,
					const struct intel_crtc_state *old_crtc_state,
					const struct drm_connector_state *old_conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_digital_port *dig_port = enc_to_dig_port(&encoder->base);
	struct intel_hdmi *intel_hdmi = &dig_port->hdmi;

	dig_port->set_infoframes(encoder, false,
				 old_crtc_state, old_conn_state);

	intel_ddi_disable_pipe_clock(old_crtc_state);

	intel_disable_ddi_buf(encoder, old_crtc_state);

	intel_display_power_put_unchecked(dev_priv,
					  dig_port->ddi_io_power_domain);

	intel_ddi_clk_disable(encoder);

	intel_dp_dual_mode_set_tmds_output(intel_hdmi, false);
}