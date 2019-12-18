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
struct link_config_limits {int max_bpp; int min_bpp; int /*<<< orphan*/  max_clock; int /*<<< orphan*/  max_lane_count; } ;
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dp_mst_encoder {TYPE_1__* primary; } ;
struct intel_dp {int /*<<< orphan*/  mst_mgr; int /*<<< orphan*/  desc; } ;
struct TYPE_6__ {int tu; } ;
struct drm_display_mode {int /*<<< orphan*/  crtc_clock; } ;
struct TYPE_5__ {struct drm_display_mode adjusted_mode; struct drm_atomic_state* state; } ;
struct intel_crtc_state {int pipe_bpp; TYPE_3__ dp_m_n; int /*<<< orphan*/  fec_enable; int /*<<< orphan*/  port_clock; int /*<<< orphan*/  lane_count; int /*<<< orphan*/  pbn; TYPE_2__ base; } ;
struct intel_connector {void* port; } ;
struct drm_connector_state {int /*<<< orphan*/  connector; } ;
struct drm_atomic_state {int dummy; } ;
struct TYPE_4__ {struct intel_dp dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DPCD_QUIRK_CONSTANT_N ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int EDEADLK ; 
 int EINVAL ; 
 int drm_dp_atomic_find_vcpi_slots (struct drm_atomic_state*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_calc_pbn_mode (int /*<<< orphan*/ ,int) ; 
 int drm_dp_has_quirk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct intel_dp_mst_encoder* enc_to_mst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_link_compute_m_n (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 struct intel_connector* to_intel_connector (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_dp_mst_compute_link_config(struct intel_encoder *encoder,
					    struct intel_crtc_state *crtc_state,
					    struct drm_connector_state *conn_state,
					    struct link_config_limits *limits)
{
	struct drm_atomic_state *state = crtc_state->base.state;
	struct intel_dp_mst_encoder *intel_mst = enc_to_mst(&encoder->base);
	struct intel_dp *intel_dp = &intel_mst->primary->dp;
	struct intel_connector *connector =
		to_intel_connector(conn_state->connector);
	const struct drm_display_mode *adjusted_mode =
		&crtc_state->base.adjusted_mode;
	void *port = connector->port;
	bool constant_n = drm_dp_has_quirk(&intel_dp->desc,
					   DP_DPCD_QUIRK_CONSTANT_N);
	int bpp, slots = -EINVAL;

	crtc_state->lane_count = limits->max_lane_count;
	crtc_state->port_clock = limits->max_clock;

	for (bpp = limits->max_bpp; bpp >= limits->min_bpp; bpp -= 2 * 3) {
		crtc_state->pipe_bpp = bpp;

		crtc_state->pbn = drm_dp_calc_pbn_mode(adjusted_mode->crtc_clock,
						       crtc_state->pipe_bpp);

		slots = drm_dp_atomic_find_vcpi_slots(state, &intel_dp->mst_mgr,
						      port, crtc_state->pbn);
		if (slots == -EDEADLK)
			return slots;
		if (slots >= 0)
			break;
	}

	if (slots < 0) {
		DRM_DEBUG_KMS("failed finding vcpi slots:%d\n", slots);
		return slots;
	}

	intel_link_compute_m_n(crtc_state->pipe_bpp,
			       crtc_state->lane_count,
			       adjusted_mode->crtc_clock,
			       crtc_state->port_clock,
			       &crtc_state->dp_m_n,
			       constant_n, crtc_state->fec_enable);
	crtc_state->dp_m_n.tu = slots;

	return 0;
}