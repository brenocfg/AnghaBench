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
struct intel_lspcon {scalar_t__ active; } ;
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_digital_port {int /*<<< orphan*/  (* set_infoframes ) (struct intel_encoder*,int /*<<< orphan*/ ,struct intel_crtc_state const*,struct drm_connector_state const*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int /*<<< orphan*/  has_infoframe; int /*<<< orphan*/  has_pch_encoder; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct intel_digital_port* enc_to_dig_port (int /*<<< orphan*/ *) ; 
 struct intel_lspcon* enc_to_intel_lspcon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icl_map_plls_to_ports (struct intel_encoder*,struct intel_crtc_state const*) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ddi_pre_enable_dp (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_ddi_pre_enable_hdmi (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_set_cpu_fifo_underrun_reporting (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct intel_encoder*,int /*<<< orphan*/ ,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_ddi_pre_enable(struct intel_encoder *encoder,
				 const struct intel_crtc_state *crtc_state,
				 const struct drm_connector_state *conn_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum pipe pipe = crtc->pipe;

	/*
	 * When called from DP MST code:
	 * - conn_state will be NULL
	 * - encoder will be the main encoder (ie. mst->primary)
	 * - the main connector associated with this port
	 *   won't be active or linked to a crtc
	 * - crtc_state will be the state of the first stream to
	 *   be activated on this port, and it may not be the same
	 *   stream that will be deactivated last, but each stream
	 *   should have a state that is identical when it comes to
	 *   the DP link parameteres
	 */

	WARN_ON(crtc_state->has_pch_encoder);

	if (INTEL_GEN(dev_priv) >= 11)
		icl_map_plls_to_ports(encoder, crtc_state);

	intel_set_cpu_fifo_underrun_reporting(dev_priv, pipe, true);

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI)) {
		intel_ddi_pre_enable_hdmi(encoder, crtc_state, conn_state);
	} else {
		struct intel_lspcon *lspcon =
				enc_to_intel_lspcon(&encoder->base);

		intel_ddi_pre_enable_dp(encoder, crtc_state, conn_state);
		if (lspcon->active) {
			struct intel_digital_port *dig_port =
					enc_to_dig_port(&encoder->base);

			dig_port->set_infoframes(encoder,
						 crtc_state->has_infoframe,
						 crtc_state, conn_state);
		}
	}
}