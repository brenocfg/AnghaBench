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
struct drm_plane_state {scalar_t__ fb; } ;
struct drm_plane {int dummy; } ;
struct dpu_plane_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  drm_framebuffer_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct dpu_plane_state*) ; 
 struct dpu_plane_state* to_dpu_plane_state (struct drm_plane_state*) ; 

__attribute__((used)) static void dpu_plane_destroy_state(struct drm_plane *plane,
		struct drm_plane_state *state)
{
	struct dpu_plane_state *pstate;

	if (!plane || !state) {
		DPU_ERROR("invalid arg(s), plane %d state %d\n",
				plane != 0, state != 0);
		return;
	}

	pstate = to_dpu_plane_state(state);

	/* remove ref count for frame buffers */
	if (state->fb)
		drm_framebuffer_put(state->fb);

	kfree(pstate);
}