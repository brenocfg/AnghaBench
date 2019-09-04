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
struct skl_wrpll_params {int dummy; } ;
struct TYPE_3__ {int ref; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
struct drm_i915_private {TYPE_2__ cdclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 struct skl_wrpll_params* icl_dp_combo_pll_19_2MHz_values ; 
 struct skl_wrpll_params* icl_dp_combo_pll_24MHz_values ; 

__attribute__((used)) static bool icl_calc_dp_combo_pll(struct drm_i915_private *dev_priv, int clock,
				  struct skl_wrpll_params *pll_params)
{
	const struct skl_wrpll_params *params;

	params = dev_priv->cdclk.hw.ref == 24000 ?
			icl_dp_combo_pll_24MHz_values :
			icl_dp_combo_pll_19_2MHz_values;

	switch (clock) {
	case 540000:
		*pll_params = params[0];
		break;
	case 270000:
		*pll_params = params[1];
		break;
	case 162000:
		*pll_params = params[2];
		break;
	case 324000:
		*pll_params = params[3];
		break;
	case 216000:
		*pll_params = params[4];
		break;
	case 432000:
		*pll_params = params[5];
		break;
	case 648000:
		*pll_params = params[6];
		break;
	case 810000:
		*pll_params = params[7];
		break;
	default:
		MISSING_CASE(clock);
		return false;
	}

	return true;
}