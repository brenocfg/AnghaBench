#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_encoder {int dummy; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct drm_connector_state {struct drm_encoder* best_encoder; struct drm_crtc* crtc; struct drm_atomic_state* state; } ;
struct drm_connector {int dummy; } ;
struct drm_atomic_state {int dummy; } ;
struct TYPE_10__ {TYPE_2__* primary; } ;
struct TYPE_8__ {int tu; } ;
struct TYPE_9__ {TYPE_3__ dp_m_n; } ;
struct TYPE_6__ {struct drm_dp_mst_topology_mgr mst_mgr; } ;
struct TYPE_7__ {TYPE_1__ dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 scalar_t__ drm_atomic_crtc_needs_modeset (struct drm_crtc_state*) ; 
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 struct drm_connector_state* drm_atomic_get_old_connector_state (struct drm_atomic_state*,struct drm_connector*) ; 
 int drm_dp_atomic_release_vcpi_slots (struct drm_atomic_state*,struct drm_dp_mst_topology_mgr*,int) ; 
 TYPE_5__* enc_to_mst (struct drm_encoder*) ; 
 TYPE_4__* to_intel_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static int intel_dp_mst_atomic_check(struct drm_connector *connector,
		struct drm_connector_state *new_conn_state)
{
	struct drm_atomic_state *state = new_conn_state->state;
	struct drm_connector_state *old_conn_state;
	struct drm_crtc *old_crtc;
	struct drm_crtc_state *crtc_state;
	int slots, ret = 0;

	old_conn_state = drm_atomic_get_old_connector_state(state, connector);
	old_crtc = old_conn_state->crtc;
	if (!old_crtc)
		return ret;

	crtc_state = drm_atomic_get_new_crtc_state(state, old_crtc);
	slots = to_intel_crtc_state(crtc_state)->dp_m_n.tu;
	if (drm_atomic_crtc_needs_modeset(crtc_state) && slots > 0) {
		struct drm_dp_mst_topology_mgr *mgr;
		struct drm_encoder *old_encoder;

		old_encoder = old_conn_state->best_encoder;
		mgr = &enc_to_mst(old_encoder)->primary->dp.mst_mgr;

		ret = drm_dp_atomic_release_vcpi_slots(state, mgr, slots);
		if (ret)
			DRM_DEBUG_KMS("failed releasing %d vcpi slots:%d\n", slots, ret);
		else
			to_intel_crtc_state(crtc_state)->dp_m_n.tu = 0;
	}
	return ret;
}