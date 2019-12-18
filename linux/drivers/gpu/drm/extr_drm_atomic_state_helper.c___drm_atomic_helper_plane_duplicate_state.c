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
struct drm_plane_state {int /*<<< orphan*/ * fb_damage_clips; int /*<<< orphan*/ * commit; int /*<<< orphan*/ * fence; scalar_t__ fb; } ;
struct drm_plane {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_framebuffer_get (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct drm_plane_state*,int /*<<< orphan*/ ,int) ; 

void __drm_atomic_helper_plane_duplicate_state(struct drm_plane *plane,
					       struct drm_plane_state *state)
{
	memcpy(state, plane->state, sizeof(*state));

	if (state->fb)
		drm_framebuffer_get(state->fb);

	state->fence = NULL;
	state->commit = NULL;
	state->fb_damage_clips = NULL;
}