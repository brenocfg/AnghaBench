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
struct TYPE_3__ {int /*<<< orphan*/  spll; } ;
struct TYPE_4__ {TYPE_1__ hw_state; } ;
struct intel_shared_dpll {TYPE_2__ state; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPLL_CTL ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void hsw_ddi_spll_enable(struct drm_i915_private *dev_priv,
				struct intel_shared_dpll *pll)
{
	I915_WRITE(SPLL_CTL, pll->state.hw_state.spll);
	POSTING_READ(SPLL_CTL);
	udelay(20);
}