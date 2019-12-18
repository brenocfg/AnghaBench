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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_digital_port {int /*<<< orphan*/  (* set_infoframes ) (struct intel_encoder*,int /*<<< orphan*/ ,struct intel_crtc_state const*,struct drm_connector_state const*) ;} ;
struct intel_crtc_state {int /*<<< orphan*/  has_infoframe; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 struct intel_digital_port* enc_to_dig_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_hdmi_prepare (struct intel_encoder*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  stub1 (struct intel_encoder*,int /*<<< orphan*/ ,struct intel_crtc_state const*,struct drm_connector_state const*) ; 

__attribute__((used)) static void intel_hdmi_pre_enable(struct intel_encoder *encoder,
				  const struct intel_crtc_state *pipe_config,
				  const struct drm_connector_state *conn_state)
{
	struct intel_digital_port *intel_dig_port =
		enc_to_dig_port(&encoder->base);

	intel_hdmi_prepare(encoder, pipe_config);

	intel_dig_port->set_infoframes(encoder,
				       pipe_config->has_infoframe,
				       pipe_config, conn_state);
}