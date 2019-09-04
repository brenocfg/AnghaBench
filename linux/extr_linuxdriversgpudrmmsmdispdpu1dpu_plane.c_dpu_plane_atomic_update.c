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
struct drm_plane_state {int dummy; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct dpu_plane {int is_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_PLANE (struct dpu_plane*,char*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _dpu_plane_atomic_disable (struct drm_plane*,struct drm_plane_state*) ; 
 int dpu_plane_sspp_atomic_update (struct drm_plane*,struct drm_plane_state*) ; 
 int /*<<< orphan*/  dpu_plane_sspp_enabled (struct drm_plane_state*) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 

__attribute__((used)) static void dpu_plane_atomic_update(struct drm_plane *plane,
				struct drm_plane_state *old_state)
{
	struct dpu_plane *pdpu;
	struct drm_plane_state *state;

	if (!plane) {
		DPU_ERROR("invalid plane\n");
		return;
	} else if (!plane->state) {
		DPU_ERROR("invalid plane state\n");
		return;
	}

	pdpu = to_dpu_plane(plane);
	pdpu->is_error = false;
	state = plane->state;

	DPU_DEBUG_PLANE(pdpu, "\n");

	if (!dpu_plane_sspp_enabled(state)) {
		_dpu_plane_atomic_disable(plane, old_state);
	} else {
		int ret;

		ret = dpu_plane_sspp_atomic_update(plane, old_state);
		/* atomic_check should have ensured that this doesn't fail */
		WARN_ON(ret < 0);
	}
}