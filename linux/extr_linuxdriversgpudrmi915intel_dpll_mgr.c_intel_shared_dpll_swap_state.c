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
struct intel_shared_dpll {struct intel_shared_dpll_state state; } ;
struct drm_i915_private {int num_shared_dpll; struct intel_shared_dpll* shared_dplls; } ;
struct drm_atomic_state {int /*<<< orphan*/  dev; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_2__ {struct intel_shared_dpll_state* shared_dpll; int /*<<< orphan*/  dpll_set; } ;

/* Variables and functions */
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_intel_atomic_state (struct drm_atomic_state*) ; 

void intel_shared_dpll_swap_state(struct drm_atomic_state *state)
{
	struct drm_i915_private *dev_priv = to_i915(state->dev);
	struct intel_shared_dpll_state *shared_dpll;
	struct intel_shared_dpll *pll;
	enum intel_dpll_id i;

	if (!to_intel_atomic_state(state)->dpll_set)
		return;

	shared_dpll = to_intel_atomic_state(state)->shared_dpll;
	for (i = 0; i < dev_priv->num_shared_dpll; i++) {
		struct intel_shared_dpll_state tmp;

		pll = &dev_priv->shared_dplls[i];

		tmp = pll->state;
		pll->state = shared_dpll[i];
		shared_dpll[i] = tmp;
	}
}