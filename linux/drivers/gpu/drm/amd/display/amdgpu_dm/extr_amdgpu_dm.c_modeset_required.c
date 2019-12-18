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
struct drm_crtc_state {int active; int /*<<< orphan*/  enable; } ;
struct dc_stream_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_crtc_needs_modeset (struct drm_crtc_state*) ; 

__attribute__((used)) static bool modeset_required(struct drm_crtc_state *crtc_state,
			     struct dc_stream_state *new_stream,
			     struct dc_stream_state *old_stream)
{
	if (!drm_atomic_crtc_needs_modeset(crtc_state))
		return false;

	if (!crtc_state->enable)
		return false;

	return crtc_state->active;
}