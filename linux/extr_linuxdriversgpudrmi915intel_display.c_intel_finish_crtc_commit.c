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
struct intel_crtc_state {int /*<<< orphan*/  base; scalar_t__ update_pipe; } ;
struct intel_crtc {int dummy; } ;
struct intel_atomic_state {int dummy; } ;
struct TYPE_2__ {int private_flags; } ;
struct drm_crtc_state {TYPE_1__ mode; int /*<<< orphan*/  state; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int I915_MODE_FLAG_INHERITED ; 
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_crtc_arm_fifo_underrun (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_pipe_update_end (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  needs_modeset (int /*<<< orphan*/ *) ; 
 struct intel_atomic_state* to_intel_atomic_state (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void intel_finish_crtc_commit(struct drm_crtc *crtc,
				     struct drm_crtc_state *old_crtc_state)
{
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_atomic_state *old_intel_state =
		to_intel_atomic_state(old_crtc_state->state);
	struct intel_crtc_state *new_crtc_state =
		intel_atomic_get_new_crtc_state(old_intel_state, intel_crtc);

	intel_pipe_update_end(new_crtc_state);

	if (new_crtc_state->update_pipe &&
	    !needs_modeset(&new_crtc_state->base) &&
	    old_crtc_state->mode.private_flags & I915_MODE_FLAG_INHERITED)
		intel_crtc_arm_fifo_underrun(intel_crtc, new_crtc_state);
}