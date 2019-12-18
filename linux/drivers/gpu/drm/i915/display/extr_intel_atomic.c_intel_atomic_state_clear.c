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
struct intel_atomic_state {int dpll_set; int modeset; int /*<<< orphan*/  base; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_state_default_clear (int /*<<< orphan*/ *) ; 
 struct intel_atomic_state* to_intel_atomic_state (struct drm_atomic_state*) ; 

void intel_atomic_state_clear(struct drm_atomic_state *s)
{
	struct intel_atomic_state *state = to_intel_atomic_state(s);
	drm_atomic_state_default_clear(&state->base);
	state->dpll_set = state->modeset = false;
}