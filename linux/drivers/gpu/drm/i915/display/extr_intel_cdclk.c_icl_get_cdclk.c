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
struct intel_cdclk_state {int bypass; int ref; int vco; int cdclk; int /*<<< orphan*/  voltage_level; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int BXT_CDCLK_CD2X_DIV_SEL_MASK ; 
 int /*<<< orphan*/  BXT_DE_PLL_ENABLE ; 
 int BXT_DE_PLL_LOCK ; 
 int BXT_DE_PLL_PLL_ENABLE ; 
 int BXT_DE_PLL_RATIO_MASK ; 
 int /*<<< orphan*/  CDCLK_CTL ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
#define  ICL_DSSM_CDCLK_PLL_REFCLK_19_2MHz 130 
#define  ICL_DSSM_CDCLK_PLL_REFCLK_24MHz 129 
#define  ICL_DSSM_CDCLK_PLL_REFCLK_38_4MHz 128 
 int ICL_DSSM_CDCLK_PLL_REFCLK_MASK ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  SKL_DSSM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  icl_calc_voltage_level (struct drm_i915_private*,int) ; 

__attribute__((used)) static void icl_get_cdclk(struct drm_i915_private *dev_priv,
			  struct intel_cdclk_state *cdclk_state)
{
	u32 val;

	cdclk_state->bypass = 50000;

	val = I915_READ(SKL_DSSM);
	switch (val & ICL_DSSM_CDCLK_PLL_REFCLK_MASK) {
	default:
		MISSING_CASE(val);
		/* fall through */
	case ICL_DSSM_CDCLK_PLL_REFCLK_24MHz:
		cdclk_state->ref = 24000;
		break;
	case ICL_DSSM_CDCLK_PLL_REFCLK_19_2MHz:
		cdclk_state->ref = 19200;
		break;
	case ICL_DSSM_CDCLK_PLL_REFCLK_38_4MHz:
		cdclk_state->ref = 38400;
		break;
	}

	val = I915_READ(BXT_DE_PLL_ENABLE);
	if ((val & BXT_DE_PLL_PLL_ENABLE) == 0 ||
	    (val & BXT_DE_PLL_LOCK) == 0) {
		/*
		 * CDCLK PLL is disabled, the VCO/ratio doesn't matter, but
		 * setting it to zero is a way to signal that.
		 */
		cdclk_state->vco = 0;
		cdclk_state->cdclk = cdclk_state->bypass;
		goto out;
	}

	cdclk_state->vco = (val & BXT_DE_PLL_RATIO_MASK) * cdclk_state->ref;

	val = I915_READ(CDCLK_CTL);
	WARN_ON((val & BXT_CDCLK_CD2X_DIV_SEL_MASK) != 0);

	cdclk_state->cdclk = cdclk_state->vco / 2;

out:
	/*
	 * Can't read this out :( Let's assume it's
	 * at least what the CDCLK frequency requires.
	 */
	cdclk_state->voltage_level =
		icl_calc_voltage_level(dev_priv, cdclk_state->cdclk);
}