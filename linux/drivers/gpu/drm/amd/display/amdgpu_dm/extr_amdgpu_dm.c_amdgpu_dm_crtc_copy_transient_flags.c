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
struct drm_crtc_state {int dummy; } ;
struct dc_stream_state {int /*<<< orphan*/  mode_changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_crtc_needs_modeset (struct drm_crtc_state*) ; 

__attribute__((used)) static void amdgpu_dm_crtc_copy_transient_flags(struct drm_crtc_state *crtc_state,
						struct dc_stream_state *stream_state)
{
	stream_state->mode_changed = drm_atomic_crtc_needs_modeset(crtc_state);
}