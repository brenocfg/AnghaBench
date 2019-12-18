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
struct intel_dpll_hw_state {int /*<<< orphan*/  cfgcr1; int /*<<< orphan*/  cfgcr0; } ;
struct TYPE_3__ {struct intel_dpll_hw_state hw_state; } ;
struct intel_shared_dpll {TYPE_2__* info; TYPE_1__ state; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 int const DPLL_ID_EHL_DPLL4 ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICL_DPLL_CFGCR0 (int const) ; 
 int /*<<< orphan*/  ICL_DPLL_CFGCR1 (int const) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_ELKHARTLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TGL_DPLL_CFGCR0 (int const) ; 
 int /*<<< orphan*/  TGL_DPLL_CFGCR1 (int const) ; 

__attribute__((used)) static void icl_dpll_write(struct drm_i915_private *dev_priv,
			   struct intel_shared_dpll *pll)
{
	struct intel_dpll_hw_state *hw_state = &pll->state.hw_state;
	const enum intel_dpll_id id = pll->info->id;
	i915_reg_t cfgcr0_reg, cfgcr1_reg;

	if (INTEL_GEN(dev_priv) >= 12) {
		cfgcr0_reg = TGL_DPLL_CFGCR0(id);
		cfgcr1_reg = TGL_DPLL_CFGCR1(id);
	} else {
		if (IS_ELKHARTLAKE(dev_priv) && id == DPLL_ID_EHL_DPLL4) {
			cfgcr0_reg = ICL_DPLL_CFGCR0(4);
			cfgcr1_reg = ICL_DPLL_CFGCR1(4);
		} else {
			cfgcr0_reg = ICL_DPLL_CFGCR0(id);
			cfgcr1_reg = ICL_DPLL_CFGCR1(id);
		}
	}

	I915_WRITE(cfgcr0_reg, hw_state->cfgcr0);
	I915_WRITE(cfgcr1_reg, hw_state->cfgcr1);
	POSTING_READ(cfgcr1_reg);
}