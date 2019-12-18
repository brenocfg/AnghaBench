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
typedef  int u32 ;
struct intel_shared_dpll {TYPE_1__* info; } ;
struct drm_i915_private {int pch_ssc_use; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int BIT (int const) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRPLL_CTL (int const) ; 
 int WRPLL_PLL_ENABLE ; 
 int /*<<< orphan*/  intel_init_pch_refclk (struct drm_i915_private*) ; 

__attribute__((used)) static void hsw_ddi_wrpll_disable(struct drm_i915_private *dev_priv,
				  struct intel_shared_dpll *pll)
{
	const enum intel_dpll_id id = pll->info->id;
	u32 val;

	val = I915_READ(WRPLL_CTL(id));
	I915_WRITE(WRPLL_CTL(id), val & ~WRPLL_PLL_ENABLE);
	POSTING_READ(WRPLL_CTL(id));

	/*
	 * Try to set up the PCH reference clock once all DPLLs
	 * that depend on it have been shut down.
	 */
	if (dev_priv->pch_ssc_use & BIT(id))
		intel_init_pch_refclk(dev_priv);
}