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
struct TYPE_5__ {int /*<<< orphan*/  dpll; } ;
struct TYPE_6__ {TYPE_2__ hw_state; } ;
struct intel_shared_dpll {TYPE_3__ state; TYPE_1__* info; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_DPLL (int const) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibx_assert_pch_refclk_enabled (struct drm_i915_private*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ibx_pch_dpll_enable(struct drm_i915_private *dev_priv,
				struct intel_shared_dpll *pll)
{
	const enum intel_dpll_id id = pll->info->id;

	/* PCH refclock must be enabled first */
	ibx_assert_pch_refclk_enabled(dev_priv);

	I915_WRITE(PCH_DPLL(id), pll->state.hw_state.dpll);

	/* Wait for the clocks to stabilize. */
	POSTING_READ(PCH_DPLL(id));
	udelay(150);

	/* The pixel multiplier can only be updated once the
	 * DPLL is enabled and the clocks are stable.
	 *
	 * So write it again.
	 */
	I915_WRITE(PCH_DPLL(id), pll->state.hw_state.dpll);
	POSTING_READ(PCH_DPLL(id));
	udelay(200);
}