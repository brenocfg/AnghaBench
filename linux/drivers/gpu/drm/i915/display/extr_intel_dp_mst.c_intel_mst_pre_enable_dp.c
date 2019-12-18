#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_3__ base; } ;
struct intel_dp_mst_encoder {struct intel_connector* connector; struct intel_digital_port* primary; } ;
struct intel_dp {scalar_t__ active_mst_links; int /*<<< orphan*/  mst_mgr; } ;
struct TYPE_5__ {int port; int /*<<< orphan*/  (* pre_enable ) (TYPE_2__*,struct intel_crtc_state const*,int /*<<< orphan*/ *) ;} ;
struct intel_digital_port {TYPE_2__ base; struct intel_dp dp; } ;
struct TYPE_4__ {int /*<<< orphan*/  tu; } ;
struct intel_crtc_state {TYPE_1__ dp_m_n; int /*<<< orphan*/  pbn; } ;
struct intel_connector {int /*<<< orphan*/  port; struct intel_encoder* encoder; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int /*<<< orphan*/  connector; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DP_TP_STATUS (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,scalar_t__) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_dp_mst_allocate_vcpi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_send_power_updown_phy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int drm_dp_update_payload_part1 (int /*<<< orphan*/ *) ; 
 struct intel_dp_mst_encoder* enc_to_mst (TYPE_3__*) ; 
 int /*<<< orphan*/  intel_ddi_enable_pipe_clock (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_dp_sink_dpms (struct intel_dp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct intel_crtc_state const*,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_connector* to_intel_connector (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_mst_pre_enable_dp(struct intel_encoder *encoder,
				    const struct intel_crtc_state *pipe_config,
				    const struct drm_connector_state *conn_state)
{
	struct intel_dp_mst_encoder *intel_mst = enc_to_mst(&encoder->base);
	struct intel_digital_port *intel_dig_port = intel_mst->primary;
	struct intel_dp *intel_dp = &intel_dig_port->dp;
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = intel_dig_port->base.port;
	struct intel_connector *connector =
		to_intel_connector(conn_state->connector);
	int ret;
	u32 temp;

	/* MST encoders are bound to a crtc, not to a connector,
	 * force the mapping here for get_hw_state.
	 */
	connector->encoder = encoder;
	intel_mst->connector = connector;

	DRM_DEBUG_KMS("active links %d\n", intel_dp->active_mst_links);

	if (intel_dp->active_mst_links == 0)
		intel_dp_sink_dpms(intel_dp, DRM_MODE_DPMS_ON);

	drm_dp_send_power_updown_phy(&intel_dp->mst_mgr, connector->port, true);

	if (intel_dp->active_mst_links == 0)
		intel_dig_port->base.pre_enable(&intel_dig_port->base,
						pipe_config, NULL);

	ret = drm_dp_mst_allocate_vcpi(&intel_dp->mst_mgr,
				       connector->port,
				       pipe_config->pbn,
				       pipe_config->dp_m_n.tu);
	if (!ret)
		DRM_ERROR("failed to allocate vcpi\n");

	intel_dp->active_mst_links++;
	temp = I915_READ(DP_TP_STATUS(port));
	I915_WRITE(DP_TP_STATUS(port), temp);

	ret = drm_dp_update_payload_part1(&intel_dp->mst_mgr);

	intel_ddi_enable_pipe_clock(pipe_config);
}