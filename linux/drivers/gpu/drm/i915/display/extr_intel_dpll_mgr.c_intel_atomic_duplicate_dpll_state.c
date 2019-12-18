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
struct intel_shared_dpll_state {int dummy; } ;
struct intel_shared_dpll {struct intel_shared_dpll_state state; } ;
struct drm_i915_private {int num_shared_dpll; struct intel_shared_dpll* shared_dplls; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;

/* Variables and functions */

__attribute__((used)) static void
intel_atomic_duplicate_dpll_state(struct drm_i915_private *dev_priv,
				  struct intel_shared_dpll_state *shared_dpll)
{
	enum intel_dpll_id i;

	/* Copy shared dpll state */
	for (i = 0; i < dev_priv->num_shared_dpll; i++) {
		struct intel_shared_dpll *pll = &dev_priv->shared_dplls[i];

		shared_dpll[i] = pll->state;
	}
}