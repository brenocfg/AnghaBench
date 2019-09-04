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
 int /*<<< orphan*/  BXT_DE_PLL_ENABLE ; 
 int BXT_DE_PLL_LOCK ; 
 int BXT_DE_PLL_PLL_ENABLE ; 
 int CNL_CDCLK_PLL_RATIO_MASK ; 
 int CNL_DSSM_CDCLK_PLL_REFCLK_24MHz ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKL_DSSM ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static void cnl_cdclk_pll_update(struct drm_i915_private *dev_priv,
				 struct intel_cdclk_state *cdclk_state)
{
	u32 val;

	if (I915_READ(SKL_DSSM) & CNL_DSSM_CDCLK_PLL_REFCLK_24MHz)
		cdclk_state->ref = 24000;
	else
		cdclk_state->ref = 19200;

	cdclk_state->vco = 0;

	val = I915_READ(BXT_DE_PLL_ENABLE);
	if ((val & BXT_DE_PLL_PLL_ENABLE) == 0)
		return;

	if (WARN_ON((val & BXT_DE_PLL_LOCK) == 0))
		return;

	cdclk_state->vco = (val & CNL_CDCLK_PLL_RATIO_MASK) * cdclk_state->ref;
}