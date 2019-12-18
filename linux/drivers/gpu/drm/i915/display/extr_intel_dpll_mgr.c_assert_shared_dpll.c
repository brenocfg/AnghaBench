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
struct intel_shared_dpll {TYPE_2__* info; } ;
struct intel_dpll_hw_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; TYPE_1__* funcs; } ;
struct TYPE_3__ {int (* get_hw_state ) (struct drm_i915_private*,struct intel_shared_dpll*,struct intel_dpll_hw_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  I915_STATE_WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onoff (int) ; 
 int stub1 (struct drm_i915_private*,struct intel_shared_dpll*,struct intel_dpll_hw_state*) ; 

void assert_shared_dpll(struct drm_i915_private *dev_priv,
			struct intel_shared_dpll *pll,
			bool state)
{
	bool cur_state;
	struct intel_dpll_hw_state hw_state;

	if (WARN(!pll, "asserting DPLL %s with no DPLL\n", onoff(state)))
		return;

	cur_state = pll->info->funcs->get_hw_state(dev_priv, pll, &hw_state);
	I915_STATE_WARN(cur_state != state,
	     "%s assertion failure (expected %s, current %s)\n",
			pll->info->name, onoff(state), onoff(cur_state));
}