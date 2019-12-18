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
struct drm_plane_state {int /*<<< orphan*/  fb_damage_clips; scalar_t__ commit; scalar_t__ fence; scalar_t__ fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_put (scalar_t__) ; 
 int /*<<< orphan*/  drm_crtc_commit_put (scalar_t__) ; 
 int /*<<< orphan*/  drm_framebuffer_put (scalar_t__) ; 
 int /*<<< orphan*/  drm_property_blob_put (int /*<<< orphan*/ ) ; 

void __drm_atomic_helper_plane_destroy_state(struct drm_plane_state *state)
{
	if (state->fb)
		drm_framebuffer_put(state->fb);

	if (state->fence)
		dma_fence_put(state->fence);

	if (state->commit)
		drm_crtc_commit_put(state->commit);

	drm_property_blob_put(state->fb_damage_clips);
}