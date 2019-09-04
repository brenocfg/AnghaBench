#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_7__* fb; } ;
struct intel_plane_state {int scaler_id; TYPE_8__ base; } ;
struct intel_plane {int /*<<< orphan*/  pipe; } ;
struct TYPE_13__ {int planes_changed; struct drm_atomic_state* state; } ;
struct intel_crtc_scaler_state {int scaler_users; int scaler_id; TYPE_9__* scalers; } ;
struct intel_crtc_state {TYPE_4__ base; struct intel_crtc_scaler_state scaler_state; } ;
struct TYPE_10__ {int id; } ;
struct TYPE_11__ {TYPE_1__ base; } ;
struct intel_crtc {int num_scalers; int /*<<< orphan*/  pipe; TYPE_2__ base; } ;
struct intel_atomic_state {int dummy; } ;
struct drm_plane_state {int dummy; } ;
struct TYPE_14__ {int id; } ;
struct drm_plane {TYPE_5__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; } ;
struct drm_atomic_state {TYPE_3__* planes; } ;
struct TYPE_18__ {int in_use; int /*<<< orphan*/  mode; } ;
struct TYPE_16__ {TYPE_6__* format; } ;
struct TYPE_15__ {scalar_t__ format; } ;
struct TYPE_12__ {struct drm_plane* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 scalar_t__ DRM_FORMAT_NV12 ; 
 int EINVAL ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct drm_plane_state*) ; 
 int /*<<< orphan*/  IS_GEMINILAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_SKYLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPE_C ; 
 int /*<<< orphan*/  PS_SCALER_MODE_DYN ; 
 int /*<<< orphan*/  PS_SCALER_MODE_HQ ; 
 int /*<<< orphan*/  PS_SCALER_MODE_PLANAR ; 
 int PTR_ERR (struct drm_plane_state*) ; 
 int SKL_CRTC_INDEX ; 
 int /*<<< orphan*/  SKL_PS_SCALER_MODE_NV12 ; 
 scalar_t__ WARN_ON (int) ; 
 struct drm_plane_state* drm_atomic_get_plane_state (struct drm_atomic_state*,struct drm_plane*) ; 
 struct drm_plane* drm_plane_from_index (int /*<<< orphan*/ *,int) ; 
 int hweight32 (int) ; 
 struct intel_plane_state* intel_atomic_get_new_plane_state (struct intel_atomic_state*,struct intel_plane*) ; 
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
	int i, j;

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
			if (WARN_ON(intel_plane->pipe != intel_crtc->pipe)) {
				continue;
			}

			plane_state = intel_atomic_get_new_plane_state(intel_state,
								       intel_plane);
			scaler_id = &plane_state->scaler_id;
		}

		if (*scaler_id < 0) {
			/* find a free scaler */
			for (j = 0; j < intel_crtc->num_scalers; j++) {
				if (!scaler_state->scalers[j].in_use) {
					scaler_state->scalers[j].in_use = 1;
					*scaler_id = j;
					DRM_DEBUG_KMS("Attached scaler id %u.%u to %s:%d\n",
						intel_crtc->pipe, *scaler_id, name, idx);
					break;
				}
			}
		}

		if (WARN_ON(*scaler_id < 0)) {
			DRM_DEBUG_KMS("Cannot find scaler for %s:%d\n", name, idx);
			continue;
		}

		/* set scaler mode */
		if ((INTEL_GEN(dev_priv) >= 9) &&
		    plane_state && plane_state->base.fb &&
		    plane_state->base.fb->format->format ==
		    DRM_FORMAT_NV12) {
			if (INTEL_GEN(dev_priv) == 9 &&
			    !IS_GEMINILAKE(dev_priv) &&
			    !IS_SKYLAKE(dev_priv))
				scaler_state->scalers[*scaler_id].mode =
					SKL_PS_SCALER_MODE_NV12;
			else
				scaler_state->scalers[*scaler_id].mode =
					PS_SCALER_MODE_PLANAR;
		} else if (num_scalers_need == 1 && intel_crtc->pipe != PIPE_C) {
			/*
			 * when only 1 scaler is in use on either pipe A or B,
			 * scaler 0 operates in high quality (HQ) mode.
			 * In this case use scaler 0 to take advantage of HQ mode
			 */
			*scaler_id = 0;
			scaler_state->scalers[0].in_use = 1;
			scaler_state->scalers[0].mode = PS_SCALER_MODE_HQ;
			scaler_state->scalers[1].in_use = 0;
		} else {
			scaler_state->scalers[*scaler_id].mode = PS_SCALER_MODE_DYN;
		}
	}

	return 0;
}