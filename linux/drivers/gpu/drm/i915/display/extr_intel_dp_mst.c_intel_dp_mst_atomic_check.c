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
struct intel_connector {int /*<<< orphan*/  port; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct drm_crtc_state {scalar_t__ enable; } ;
struct drm_crtc {int dummy; } ;
struct drm_connector_state {int /*<<< orphan*/  best_encoder; struct drm_crtc* crtc; } ;
struct drm_connector {int dummy; } ;
struct drm_atomic_state {int dummy; } ;
struct TYPE_6__ {TYPE_2__* primary; } ;
struct TYPE_4__ {struct drm_dp_mst_topology_mgr mst_mgr; } ;
struct TYPE_5__ {TYPE_1__ dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_crtc_needs_modeset (struct drm_crtc_state*) ; 
 struct drm_connector_state* drm_atomic_get_new_connector_state (struct drm_atomic_state*,struct drm_connector*) ; 
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 struct drm_connector_state* drm_atomic_get_old_connector_state (struct drm_atomic_state*,struct drm_connector*) ; 
 int drm_dp_atomic_release_vcpi_slots (struct drm_atomic_state*,struct drm_dp_mst_topology_mgr*,int /*<<< orphan*/ ) ; 
 TYPE_3__* enc_to_mst (int /*<<< orphan*/ ) ; 
 int intel_digital_connector_atomic_check (struct drm_connector*,struct drm_atomic_state*) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static int
intel_dp_mst_atomic_check(struct drm_connector *connector,
			  struct drm_atomic_state *state)
{
	struct drm_connector_state *new_conn_state =
		drm_atomic_get_new_connector_state(state, connector);
	struct drm_connector_state *old_conn_state =
		drm_atomic_get_old_connector_state(state, connector);
	struct intel_connector *intel_connector =
		to_intel_connector(connector);
	struct drm_crtc *new_crtc = new_conn_state->crtc;
	struct drm_crtc_state *crtc_state;
	struct drm_dp_mst_topology_mgr *mgr;
	int ret;

	ret = intel_digital_connector_atomic_check(connector, state);
	if (ret)
		return ret;

	if (!old_conn_state->crtc)
		return 0;

	/* We only want to free VCPI if this state disables the CRTC on this
	 * connector
	 */
	if (new_crtc) {
		crtc_state = drm_atomic_get_new_crtc_state(state, new_crtc);

		if (!crtc_state ||
		    !drm_atomic_crtc_needs_modeset(crtc_state) ||
		    crtc_state->enable)
			return 0;
	}

	mgr = &enc_to_mst(old_conn_state->best_encoder)->primary->dp.mst_mgr;
	ret = drm_dp_atomic_release_vcpi_slots(state, mgr,
					       intel_connector->port);

	return ret;
}