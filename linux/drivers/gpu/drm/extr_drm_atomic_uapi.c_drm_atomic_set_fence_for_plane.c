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
struct drm_plane_state {struct dma_fence* fence; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 

void
drm_atomic_set_fence_for_plane(struct drm_plane_state *plane_state,
			       struct dma_fence *fence)
{
	if (plane_state->fence) {
		dma_fence_put(fence);
		return;
	}

	plane_state->fence = fence;
}