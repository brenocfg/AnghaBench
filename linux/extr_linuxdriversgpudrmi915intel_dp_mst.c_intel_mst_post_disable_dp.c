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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dp_mst_encoder {int /*<<< orphan*/ * connector; struct intel_digital_port* primary; } ;
struct intel_dp {scalar_t__ active_mst_links; int /*<<< orphan*/  mst_mgr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* post_disable ) (TYPE_1__*,struct intel_crtc_state const*,int /*<<< orphan*/ *) ;} ;
struct intel_digital_port {TYPE_1__ base; struct intel_dp dp; } ;
struct intel_crtc_state {int dummy; } ;
struct intel_connector {int /*<<< orphan*/  port; } ;
struct drm_connector_state {int /*<<< orphan*/  connector; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,scalar_t__) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  drm_dp_check_act_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dp_mst_deallocate_vcpi (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_send_power_updown_phy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_dp_update_payload_part2 (int /*<<< orphan*/ *) ; 
 struct intel_dp_mst_encoder* enc_to_mst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_ddi_disable_pipe_clock (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_dp_sink_dpms (struct intel_dp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct intel_crtc_state const*,int /*<<< orphan*/ *) ; 
 struct intel_connector* to_intel_connector (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_mst_post_disable_dp(struct intel_encoder *encoder,
				      const struct intel_crtc_state *old_crtc_state,
				      const struct drm_connector_state *old_conn_state)
{
	struct intel_dp_mst_encoder *intel_mst = enc_to_mst(&encoder->base);
	struct intel_digital_port *intel_dig_port = intel_mst->primary;
	struct intel_dp *intel_dp = &intel_dig_port->dp;
	struct intel_connector *connector =
		to_intel_connector(old_conn_state->connector);

	intel_ddi_disable_pipe_clock(old_crtc_state);

	/* this can fail */
	drm_dp_check_act_status(&intel_dp->mst_mgr);
	/* and this can also fail */
	drm_dp_update_payload_part2(&intel_dp->mst_mgr);

	drm_dp_mst_deallocate_vcpi(&intel_dp->mst_mgr, connector->port);

	/*
	 * Power down mst path before disabling the port, otherwise we end
	 * up getting interrupts from the sink upon detecting link loss.
	 */
	drm_dp_send_power_updown_phy(&intel_dp->mst_mgr, connector->port,
				     false);

	intel_dp->active_mst_links--;

	intel_mst->connector = NULL;
	if (intel_dp->active_mst_links == 0) {
		intel_dp_sink_dpms(intel_dp, DRM_MODE_DPMS_OFF);
		intel_dig_port->base.post_disable(&intel_dig_port->base,
						  old_crtc_state, NULL);
	}

	DRM_DEBUG_KMS("active links %d\n", intel_dp->active_mst_links);
}