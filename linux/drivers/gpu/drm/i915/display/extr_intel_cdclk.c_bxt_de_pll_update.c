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
typedef  int u32 ;
struct intel_cdclk_state {int ref; int vco; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_DE_PLL_CTL ; 
 int /*<<< orphan*/  BXT_DE_PLL_ENABLE ; 
 int BXT_DE_PLL_LOCK ; 
 int BXT_DE_PLL_PLL_ENABLE ; 
 int BXT_DE_PLL_RATIO_MASK ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static void bxt_de_pll_update(struct drm_i915_private *dev_priv,
			      struct intel_cdclk_state *cdclk_state)
{
	u32 val;

	cdclk_state->ref = 19200;
	cdclk_state->vco = 0;

	val = I915_READ(BXT_DE_PLL_ENABLE);
	if ((val & BXT_DE_PLL_PLL_ENABLE) == 0)
		return;

	if (WARN_ON((val & BXT_DE_PLL_LOCK) == 0))
		return;

	val = I915_READ(BXT_DE_PLL_CTL);
	cdclk_state->vco = (val & BXT_DE_PLL_RATIO_MASK) * cdclk_state->ref;
}