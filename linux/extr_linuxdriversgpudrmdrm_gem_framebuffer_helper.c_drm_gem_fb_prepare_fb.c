#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_plane_state {int /*<<< orphan*/  fb; } ;
struct drm_plane {int dummy; } ;
struct dma_fence {int dummy; } ;
struct dma_buf {int /*<<< orphan*/  resv; } ;
struct TYPE_2__ {struct dma_buf* dma_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_set_fence_for_plane (struct drm_plane_state*,struct dma_fence*) ; 
 TYPE_1__* drm_gem_fb_get_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dma_fence* reservation_object_get_excl_rcu (int /*<<< orphan*/ ) ; 

int drm_gem_fb_prepare_fb(struct drm_plane *plane,
			  struct drm_plane_state *state)
{
	struct dma_buf *dma_buf;
	struct dma_fence *fence;

	if (!state->fb)
		return 0;

	dma_buf = drm_gem_fb_get_obj(state->fb, 0)->dma_buf;
	if (dma_buf) {
		fence = reservation_object_get_excl_rcu(dma_buf->resv);
		drm_atomic_set_fence_for_plane(state, fence);
	}

	return 0;
}