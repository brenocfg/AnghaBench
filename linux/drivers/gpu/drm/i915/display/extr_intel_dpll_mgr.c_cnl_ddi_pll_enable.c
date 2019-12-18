#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int cfgcr0; int cfgcr1; } ;
struct TYPE_6__ {TYPE_2__ hw_state; } ;
struct intel_shared_dpll {TYPE_3__ state; TYPE_1__* info; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_DPLL_CFGCR0 (int const) ; 
 int /*<<< orphan*/  CNL_DPLL_CFGCR1 (int const) ; 
 int /*<<< orphan*/  CNL_DPLL_ENABLE (int const) ; 
 int DPLL_CFGCR0_HDMI_MODE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int const) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int PLL_ENABLE ; 
 int /*<<< orphan*/  PLL_LOCK ; 
 int PLL_POWER_ENABLE ; 
 int /*<<< orphan*/  PLL_POWER_STATE ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_de_wait_for_set (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cnl_ddi_pll_enable(struct drm_i915_private *dev_priv,
			       struct intel_shared_dpll *pll)
{
	const enum intel_dpll_id id = pll->info->id;
	u32 val;

	/* 1. Enable DPLL power in DPLL_ENABLE. */
	val = I915_READ(CNL_DPLL_ENABLE(id));
	val |= PLL_POWER_ENABLE;
	I915_WRITE(CNL_DPLL_ENABLE(id), val);

	/* 2. Wait for DPLL power state enabled in DPLL_ENABLE. */
	if (intel_de_wait_for_set(dev_priv, CNL_DPLL_ENABLE(id),
				  PLL_POWER_STATE, 5))
		DRM_ERROR("PLL %d Power not enabled\n", id);

	/*
	 * 3. Configure DPLL_CFGCR0 to set SSC enable/disable,
	 * select DP mode, and set DP link rate.
	 */
	val = pll->state.hw_state.cfgcr0;
	I915_WRITE(CNL_DPLL_CFGCR0(id), val);

	/* 4. Reab back to ensure writes completed */
	POSTING_READ(CNL_DPLL_CFGCR0(id));

	/* 3. Configure DPLL_CFGCR0 */
	/* Avoid touch CFGCR1 if HDMI mode is not enabled */
	if (pll->state.hw_state.cfgcr0 & DPLL_CFGCR0_HDMI_MODE) {
		val = pll->state.hw_state.cfgcr1;
		I915_WRITE(CNL_DPLL_CFGCR1(id), val);
		/* 4. Reab back to ensure writes completed */
		POSTING_READ(CNL_DPLL_CFGCR1(id));
	}

	/*
	 * 5. If the frequency will result in a change to the voltage
	 * requirement, follow the Display Voltage Frequency Switching
	 * Sequence Before Frequency Change
	 *
	 * Note: DVFS is actually handled via the cdclk code paths,
	 * hence we do nothing here.
	 */

	/* 6. Enable DPLL in DPLL_ENABLE. */
	val = I915_READ(CNL_DPLL_ENABLE(id));
	val |= PLL_ENABLE;
	I915_WRITE(CNL_DPLL_ENABLE(id), val);

	/* 7. Wait for PLL lock status in DPLL_ENABLE. */
	if (intel_de_wait_for_set(dev_priv, CNL_DPLL_ENABLE(id), PLL_LOCK, 5))
		DRM_ERROR("PLL %d not locked\n", id);

	/*
	 * 8. If the frequency will result in a change to the voltage
	 * requirement, follow the Display Voltage Frequency Switching
	 * Sequence After Frequency Change
	 *
	 * Note: DVFS is actually handled via the cdclk code paths,
	 * hence we do nothing here.
	 */

	/*
	 * 9. turn on the clock for the DDI and map the DPLL to the DDI
	 * Done at intel_ddi_clk_select
	 */
}