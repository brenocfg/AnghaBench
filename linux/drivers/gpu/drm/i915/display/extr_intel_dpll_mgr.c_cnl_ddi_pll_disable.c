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
typedef  int /*<<< orphan*/  u32 ;
struct intel_shared_dpll {TYPE_1__* info; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_DPLL_ENABLE (int const) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int const) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLL_ENABLE ; 
 int /*<<< orphan*/  PLL_LOCK ; 
 int /*<<< orphan*/  PLL_POWER_ENABLE ; 
 int /*<<< orphan*/  PLL_POWER_STATE ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cnl_ddi_pll_disable(struct drm_i915_private *dev_priv,
				struct intel_shared_dpll *pll)
{
	const enum intel_dpll_id id = pll->info->id;
	u32 val;

	/*
	 * 1. Configure DPCLKA_CFGCR0 to turn off the clock for the DDI.
	 * Done at intel_ddi_post_disable
	 */

	/*
	 * 2. If the frequency will result in a change to the voltage
	 * requirement, follow the Display Voltage Frequency Switching
	 * Sequence Before Frequency Change
	 *
	 * Note: DVFS is actually handled via the cdclk code paths,
	 * hence we do nothing here.
	 */

	/* 3. Disable DPLL through DPLL_ENABLE. */
	val = I915_READ(CNL_DPLL_ENABLE(id));
	val &= ~PLL_ENABLE;
	I915_WRITE(CNL_DPLL_ENABLE(id), val);

	/* 4. Wait for PLL not locked status in DPLL_ENABLE. */
	if (intel_de_wait_for_clear(dev_priv, CNL_DPLL_ENABLE(id), PLL_LOCK, 5))
		DRM_ERROR("PLL %d locked\n", id);

	/*
	 * 5. If the frequency will result in a change to the voltage
	 * requirement, follow the Display Voltage Frequency Switching
	 * Sequence After Frequency Change
	 *
	 * Note: DVFS is actually handled via the cdclk code paths,
	 * hence we do nothing here.
	 */

	/* 6. Disable DPLL power in DPLL_ENABLE. */
	val = I915_READ(CNL_DPLL_ENABLE(id));
	val &= ~PLL_POWER_ENABLE;
	I915_WRITE(CNL_DPLL_ENABLE(id), val);

	/* 7. Wait for DPLL power state disabled in DPLL_ENABLE. */
	if (intel_de_wait_for_clear(dev_priv, CNL_DPLL_ENABLE(id),
				    PLL_POWER_STATE, 5))
		DRM_ERROR("PLL %d Power not disabled\n", id);
}