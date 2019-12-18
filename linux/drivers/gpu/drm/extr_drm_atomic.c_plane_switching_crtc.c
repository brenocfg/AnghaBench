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
struct drm_plane_state {scalar_t__ crtc; } ;

/* Variables and functions */

__attribute__((used)) static bool
plane_switching_crtc(const struct drm_plane_state *old_plane_state,
		     const struct drm_plane_state *new_plane_state)
{
	if (!old_plane_state->crtc || !new_plane_state->crtc)
		return false;

	if (old_plane_state->crtc == new_plane_state->crtc)
		return false;

	/* This could be refined, but currently there's no helper or driver code
	 * to implement direct switching of active planes nor userspace to take
	 * advantage of more direct plane switching without the intermediate
	 * full OFF state.
	 */
	return true;
}