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
struct intel_shared_dpll_state {int dummy; } ;
struct intel_shared_dpll {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_atomic_state {int /*<<< orphan*/  dpll_set; struct intel_shared_dpll_state* shared_dpll; TYPE_1__ base; } ;
struct drm_i915_private {int num_shared_dpll; struct intel_shared_dpll* shared_dplls; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;

/* Variables and functions */
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,struct intel_shared_dpll_state) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_shared_dpll_swap_state(struct intel_atomic_state *state)
{
	struct drm_i915_private *dev_priv = to_i915(state->base.dev);
	struct intel_shared_dpll_state *shared_dpll = state->shared_dpll;
	enum intel_dpll_id i;

	if (!state->dpll_set)
		return;

	for (i = 0; i < dev_priv->num_shared_dpll; i++) {
		struct intel_shared_dpll *pll =
			&dev_priv->shared_dplls[i];

		swap(pll->state, shared_dpll[i]);
	}
}