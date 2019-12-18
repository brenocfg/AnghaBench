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
struct intel_plane_state {int scaler_id; } ;
struct intel_plane {scalar_t__ pipe; } ;
struct TYPE_9__ {int planes_changed; struct drm_atomic_state* state; } ;
struct intel_crtc_scaler_state {int scaler_users; int scaler_id; } ;
struct intel_crtc_state {TYPE_4__ base; struct intel_crtc_scaler_state scaler_state; } ;
struct TYPE_6__ {int id; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
struct intel_crtc {int num_scalers; scalar_t__ pipe; TYPE_2__ base; } ;
struct intel_atomic_state {int dummy; } ;
struct drm_plane_state {int dummy; } ;
struct TYPE_10__ {int id; } ;
struct drm_plane {TYPE_5__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; } ;
struct drm_atomic_state {TYPE_3__* planes; } ;
struct TYPE_8__ {struct drm_plane* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct drm_plane_state*) ; 
 int PTR_ERR (struct drm_plane_state*) ; 
 int SKL_CRTC_INDEX ; 
 scalar_t__ WARN_ON (int) ; 
 struct drm_plane_state* drm_atomic_get_plane_state (struct drm_atomic_state*,struct drm_plane*) ; 
 struct drm_plane* drm_plane_from_index (int /*<<< orphan*/ *,int) ; 
 int hweight32 (int) ; 
 struct intel_plane_state* intel_atomic_get_new_plane_state (struct intel_atomic_state*,struct intel_plane*) ; 
 int /*<<< orphan*/  intel_atomic_setup_scaler (struct intel_crtc_scaler_state*,int,struct intel_crtc*,char const*,int,struct intel_plane_state*,int*) ; 
 struct intel_atomic_state* to_intel_atomic_state (struct drm_atomic_state*) ; 
 struct intel_plane* to_intel_plane (struct drm_plane*) ; 

int intel_atomic_setup_scalers(struct drm_i915_private *dev_priv,
			       struct intel_crtc *intel_crtc,
			       struct intel_crtc_state *crtc_state)
{
	struct drm_plane *plane = NULL;
	struct intel_plane *intel_plane;
	struct intel_plane_state *plane_state = NULL;
	struct intel_crtc_scaler_state *scaler_state =
		&crtc_state->scaler_state;
	struct drm_atomic_state *drm_state = crtc_state->base.state;
	struct intel_atomic_state *intel_state = to_intel_atomic_state(drm_state);
	int num_scalers_need;
	int i;

	num_scalers_need = hweight32(scaler_state->scaler_users);

	/*
	 * High level flow:
	 * - staged scaler requests are already in scaler_state->scaler_users
	 * - check whether staged scaling requests can be supported
	 * - add planes using scalers that aren't in current transaction
	 * - assign scalers to requested users
	 * - as part of plane commit, scalers will be committed
	 *   (i.e., either attached or detached) to respective planes in hw
	 * - as part of crtc_commit, scaler will be either attached or detached
	 *   to crtc in hw
	 */

	/* fail if required scalers > available scalers */
	if (num_scalers_need > intel_crtc->num_scalers){
		DRM_DEBUG_KMS("Too many scaling requests %d > %d\n",
			num_scalers_need, intel_crtc->num_scalers);
		return -EINVAL;
	}

	/* walkthrough scaler_users bits and start assigning scalers */
	for (i = 0; i < sizeof(scaler_state->scaler_users) * 8; i++) {
		int *scaler_id;
		const char *name;
		int idx;

		/* skip if scaler not required */
		if (!(scaler_state->scaler_users & (1 << i)))
			continue;

		if (i == SKL_CRTC_INDEX) {
			name = "CRTC";
			idx = intel_crtc->base.base.id;

			/* panel fitter case: assign as a crtc scaler */
			scaler_id = &scaler_state->scaler_id;
		} else {
			name = "PLANE";

			/* plane scaler case: assign as a plane scaler */
			/* find the plane that set the bit as scaler_user */
			plane = drm_state->planes[i].ptr;

			/*
			 * to enable/disable hq mode, add planes that are using scaler
			 * into this transaction
			 */
			if (!plane) {
				struct drm_plane_state *state;
				plane = drm_plane_from_index(&dev_priv->drm, i);
				state = drm_atomic_get_plane_state(drm_state, plane);
				if (IS_ERR(state)) {
					DRM_DEBUG_KMS("Failed to add [PLANE:%d] to drm_state\n",
						plane->base.id);
					return PTR_ERR(state);
				}

				/*
				 * the plane is added after plane checks are run,
				 * but since this plane is unchanged just do the
				 * minimum required validation.
				 */
				crtc_state->base.planes_changed = true;
			}

			intel_plane = to_intel_plane(plane);
			idx = plane->base.id;

			/* plane on different crtc cannot be a scaler user of this crtc */
			if (WARN_ON(intel_plane->pipe != intel_crtc->pipe))
				continue;

			plane_state = intel_atomic_get_new_plane_state(intel_state,
								       intel_plane);
			scaler_id = &plane_state->scaler_id;
		}

		intel_atomic_setup_scaler(scaler_state, num_scalers_need,
					  intel_crtc, name, idx,
					  plane_state, scaler_id);
	}

	return 0;
}