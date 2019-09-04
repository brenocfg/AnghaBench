#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_6__ base; } ;
struct intel_dp_mst_encoder {struct intel_digital_port* primary; } ;
struct TYPE_8__ {int bpc; } ;
struct TYPE_9__ {TYPE_2__ test_data; } ;
struct intel_dp {int /*<<< orphan*/  mst_mgr; TYPE_3__ compliance; int /*<<< orphan*/  desc; } ;
struct intel_digital_port {struct intel_dp dp; } ;
struct TYPE_11__ {int tu; } ;
struct drm_display_mode {int flags; int /*<<< orphan*/  crtc_clock; } ;
struct TYPE_7__ {struct drm_display_mode adjusted_mode; struct drm_atomic_state* state; } ;
struct intel_crtc_state {int has_pch_encoder; int lane_count; int pipe_bpp; int has_audio; int pbn; int /*<<< orphan*/  lane_lat_optim_mask; TYPE_5__ dp_m_n; int /*<<< orphan*/  port_clock; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {struct drm_connector* connector; } ;
struct drm_connector {int /*<<< orphan*/  registered; } ;
struct drm_atomic_state {int dummy; } ;
struct TYPE_10__ {void* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DPCD_QUIRK_LIMITED_M_N ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxt_ddi_phy_calc_lane_lat_optim_mask (int) ; 
 int drm_dp_atomic_find_vcpi_slots (struct drm_atomic_state*,int /*<<< orphan*/ *,void*,int) ; 
 int drm_dp_calc_pbn_mode (int /*<<< orphan*/ ,int) ; 
 int drm_dp_has_quirk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_dp_mst_port_has_audio (int /*<<< orphan*/ *,void*) ; 
 struct intel_dp_mst_encoder* enc_to_mst (TYPE_6__*) ; 
 int /*<<< orphan*/  intel_ddi_compute_min_voltage_level (struct drm_i915_private*,struct intel_crtc_state*) ; 
 int intel_dp_max_lane_count (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_max_link_rate (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_link_compute_m_n (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 TYPE_4__* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static bool intel_dp_mst_compute_config(struct intel_encoder *encoder,
					struct intel_crtc_state *pipe_config,
					struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_dp_mst_encoder *intel_mst = enc_to_mst(&encoder->base);
	struct intel_digital_port *intel_dig_port = intel_mst->primary;
	struct intel_dp *intel_dp = &intel_dig_port->dp;
	struct drm_connector *connector = conn_state->connector;
	void *port = to_intel_connector(connector)->port;
	struct drm_atomic_state *state = pipe_config->base.state;
	int bpp;
	int lane_count, slots = 0;
	const struct drm_display_mode *adjusted_mode = &pipe_config->base.adjusted_mode;
	int mst_pbn;
	bool reduce_m_n = drm_dp_has_quirk(&intel_dp->desc,
					   DP_DPCD_QUIRK_LIMITED_M_N);

	if (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return false;

	pipe_config->has_pch_encoder = false;
	bpp = 24;
	if (intel_dp->compliance.test_data.bpc) {
		bpp = intel_dp->compliance.test_data.bpc * 3;
		DRM_DEBUG_KMS("Setting pipe bpp to %d\n",
			      bpp);
	}
	/*
	 * for MST we always configure max link bw - the spec doesn't
	 * seem to suggest we should do otherwise.
	 */
	lane_count = intel_dp_max_lane_count(intel_dp);

	pipe_config->lane_count = lane_count;

	pipe_config->pipe_bpp = bpp;

	pipe_config->port_clock = intel_dp_max_link_rate(intel_dp);

	if (drm_dp_mst_port_has_audio(&intel_dp->mst_mgr, port))
		pipe_config->has_audio = true;

	mst_pbn = drm_dp_calc_pbn_mode(adjusted_mode->crtc_clock, bpp);
	pipe_config->pbn = mst_pbn;

	/* Zombie connectors can't have VCPI slots */
	if (READ_ONCE(connector->registered)) {
		slots = drm_dp_atomic_find_vcpi_slots(state,
						      &intel_dp->mst_mgr,
						      port,
						      mst_pbn);
		if (slots < 0) {
			DRM_DEBUG_KMS("failed finding vcpi slots:%d\n",
				      slots);
			return false;
		}
	}

	intel_link_compute_m_n(bpp, lane_count,
			       adjusted_mode->crtc_clock,
			       pipe_config->port_clock,
			       &pipe_config->dp_m_n,
			       reduce_m_n);

	pipe_config->dp_m_n.tu = slots;

	if (IS_GEN9_LP(dev_priv))
		pipe_config->lane_lat_optim_mask =
			bxt_ddi_phy_calc_lane_lat_optim_mask(pipe_config->lane_count);

	intel_ddi_compute_min_voltage_level(dev_priv, pipe_config);

	return true;
}