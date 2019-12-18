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
struct skl_dpll_regs {int /*<<< orphan*/  ctl; } ;
struct intel_shared_dpll {TYPE_1__* info; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int LCPLL_PLL_ENABLE ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 struct skl_dpll_regs* skl_dpll_regs ; 

__attribute__((used)) static void skl_ddi_pll_disable(struct drm_i915_private *dev_priv,
				struct intel_shared_dpll *pll)
{
	const struct skl_dpll_regs *regs = skl_dpll_regs;
	const enum intel_dpll_id id = pll->info->id;

	/* the enable bit is always bit 31 */
	I915_WRITE(regs[id].ctl,
		   I915_READ(regs[id].ctl) & ~LCPLL_PLL_ENABLE);
	POSTING_READ(regs[id].ctl);
}