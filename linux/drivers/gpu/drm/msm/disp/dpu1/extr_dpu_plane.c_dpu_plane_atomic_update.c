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
struct drm_plane_state {int /*<<< orphan*/  visible; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct dpu_plane {int is_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_PLANE (struct dpu_plane*,char*) ; 
 int /*<<< orphan*/  _dpu_plane_atomic_disable (struct drm_plane*) ; 
 int /*<<< orphan*/  dpu_plane_sspp_atomic_update (struct drm_plane*) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 

__attribute__((used)) static void dpu_plane_atomic_update(struct drm_plane *plane,
				struct drm_plane_state *old_state)
{
	struct dpu_plane *pdpu = to_dpu_plane(plane);
	struct drm_plane_state *state = plane->state;

	pdpu->is_error = false;

	DPU_DEBUG_PLANE(pdpu, "\n");

	if (!state->visible) {
		_dpu_plane_atomic_disable(plane);
	} else {
		dpu_plane_sspp_atomic_update(plane);
	}
}