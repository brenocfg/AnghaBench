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
struct drm_crtc_state {scalar_t__ self_refresh_active; int /*<<< orphan*/  enable; scalar_t__ active; } ;

/* Variables and functions */
 int drm_atomic_crtc_effectively_active (struct drm_crtc_state*) ; 

__attribute__((used)) static bool
crtc_needs_disable(struct drm_crtc_state *old_state,
		   struct drm_crtc_state *new_state)
{
	/*
	 * No new_state means the crtc is off, so the only criteria is whether
	 * it's currently active or in self refresh mode.
	 */
	if (!new_state)
		return drm_atomic_crtc_effectively_active(old_state);

	/*
	 * We need to run through the crtc_funcs->disable() function if the crtc
	 * is currently on, if it's transitioning to self refresh mode, or if
	 * it's in self refresh mode and needs to be fully disabled.
	 */
	return old_state->active ||
	       (old_state->self_refresh_active && !new_state->enable) ||
	       new_state->self_refresh_active;
}