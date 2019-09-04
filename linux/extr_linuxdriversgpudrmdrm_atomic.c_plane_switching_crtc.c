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
struct drm_plane_state {scalar_t__ crtc; } ;
struct drm_plane {TYPE_1__* state; } ;
struct drm_atomic_state {int dummy; } ;
struct TYPE_2__ {scalar_t__ crtc; } ;

/* Variables and functions */

__attribute__((used)) static bool
plane_switching_crtc(struct drm_atomic_state *state,
		     struct drm_plane *plane,
		     struct drm_plane_state *plane_state)
{
	if (!plane->state->crtc || !plane_state->crtc)
		return false;

	if (plane->state->crtc == plane_state->crtc)
		return false;

	/* This could be refined, but currently there's no helper or driver code
	 * to implement direct switching of active planes nor userspace to take
	 * advantage of more direct plane switching without the intermediate
	 * full OFF state.
	 */
	return true;
}