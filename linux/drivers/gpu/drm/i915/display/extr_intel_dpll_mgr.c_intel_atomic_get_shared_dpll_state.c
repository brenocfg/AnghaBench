#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_shared_dpll_state {int dummy; } ;
struct intel_atomic_state {int dpll_set; struct intel_shared_dpll_state* shared_dpll; } ;
struct drm_atomic_state {TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  connection_mutex; } ;
struct TYPE_4__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_modeset_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_atomic_duplicate_dpll_state (int /*<<< orphan*/ ,struct intel_shared_dpll_state*) ; 
 int /*<<< orphan*/  to_i915 (TYPE_2__*) ; 
 struct intel_atomic_state* to_intel_atomic_state (struct drm_atomic_state*) ; 

__attribute__((used)) static struct intel_shared_dpll_state *
intel_atomic_get_shared_dpll_state(struct drm_atomic_state *s)
{
	struct intel_atomic_state *state = to_intel_atomic_state(s);

	WARN_ON(!drm_modeset_is_locked(&s->dev->mode_config.connection_mutex));

	if (!state->dpll_set) {
		state->dpll_set = true;

		intel_atomic_duplicate_dpll_state(to_i915(s->dev),
						  state->shared_dpll);
	}

	return state->shared_dpll;
}