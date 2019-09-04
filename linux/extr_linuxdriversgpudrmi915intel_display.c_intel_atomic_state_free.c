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
struct intel_atomic_state {int /*<<< orphan*/  commit_ready; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_state_default_release (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  i915_sw_fence_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_atomic_state*) ; 
 struct intel_atomic_state* to_intel_atomic_state (struct drm_atomic_state*) ; 

__attribute__((used)) static void intel_atomic_state_free(struct drm_atomic_state *state)
{
	struct intel_atomic_state *intel_state = to_intel_atomic_state(state);

	drm_atomic_state_default_release(state);

	i915_sw_fence_fini(&intel_state->commit_ready);

	kfree(state);
}