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
struct intel_cdclk_state {scalar_t__ vco; int /*<<< orphan*/  cdclk; int /*<<< orphan*/  voltage_level; int /*<<< orphan*/  ref; int /*<<< orphan*/  bypass; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
#define  BXT_CDCLK_CD2X_DIV_SEL_1 129 
#define  BXT_CDCLK_CD2X_DIV_SEL_2 128 
 int BXT_CDCLK_CD2X_DIV_SEL_MASK ; 
 int /*<<< orphan*/  CDCLK_CTL ; 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (scalar_t__,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  cnl_calc_voltage_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnl_cdclk_pll_update (struct drm_i915_private*,struct intel_cdclk_state*) ; 

__attribute__((used)) static void cnl_get_cdclk(struct drm_i915_private *dev_priv,
			 struct intel_cdclk_state *cdclk_state)
{
	u32 divider;
	int div;

	cnl_cdclk_pll_update(dev_priv, cdclk_state);

	cdclk_state->cdclk = cdclk_state->bypass = cdclk_state->ref;

	if (cdclk_state->vco == 0)
		goto out;

	divider = I915_READ(CDCLK_CTL) & BXT_CDCLK_CD2X_DIV_SEL_MASK;

	switch (divider) {
	case BXT_CDCLK_CD2X_DIV_SEL_1:
		div = 2;
		break;
	case BXT_CDCLK_CD2X_DIV_SEL_2:
		div = 4;
		break;
	default:
		MISSING_CASE(divider);
		return;
	}

	cdclk_state->cdclk = DIV_ROUND_CLOSEST(cdclk_state->vco, div);

 out:
	/*
	 * Can't read this out :( Let's assume it's
	 * at least what the CDCLK frequency requires.
	 */
	cdclk_state->voltage_level =
		cnl_calc_voltage_level(cdclk_state->cdclk);
}