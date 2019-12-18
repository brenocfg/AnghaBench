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
struct drm_plane_state {int /*<<< orphan*/  fb; } ;
struct drm_plane {int dummy; } ;
struct drm_gem_object {int /*<<< orphan*/  resv; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct dma_fence* dma_resv_get_excl_rcu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_set_fence_for_plane (struct drm_plane_state*,struct dma_fence*) ; 
 struct drm_gem_object* drm_gem_fb_get_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_gem_fb_prepare_fb(struct drm_plane *plane,
			  struct drm_plane_state *state)
{
	struct drm_gem_object *obj;
	struct dma_fence *fence;

	if (!state->fb)
		return 0;

	obj = drm_gem_fb_get_obj(state->fb, 0);
	fence = dma_resv_get_excl_rcu(obj->resv);
	drm_atomic_set_fence_for_plane(state, fence);

	return 0;
}