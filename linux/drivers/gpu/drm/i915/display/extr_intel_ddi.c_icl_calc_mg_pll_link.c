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
typedef  int u64 ;
typedef  int u32 ;
struct intel_dpll_hw_state {int mg_pll_div1; int mg_pll_div0; int mg_clktop2_hsclkctl; } ;
struct TYPE_3__ {int ref; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
struct drm_i915_private {TYPE_2__ cdclk; } ;

/* Variables and functions */
 int MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO_MASK ; 
 int MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO_SHIFT ; 
#define  MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_2 131 
#define  MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_3 130 
#define  MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_5 129 
#define  MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_7 128 
 int MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_MASK ; 
 int MG_PLL_DIV0_FBDIV_FRAC_MASK ; 
 int MG_PLL_DIV0_FBDIV_FRAC_SHIFT ; 
 int MG_PLL_DIV0_FBDIV_INT_MASK ; 
 int MG_PLL_DIV0_FRACNEN_H ; 
 int MG_PLL_DIV1_FBPREDIV_MASK ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int div_u64 (int,int) ; 

__attribute__((used)) static int icl_calc_mg_pll_link(struct drm_i915_private *dev_priv,
				const struct intel_dpll_hw_state *pll_state)
{
	u32 m1, m2_int, m2_frac, div1, div2, ref_clock;
	u64 tmp;

	ref_clock = dev_priv->cdclk.hw.ref;

	m1 = pll_state->mg_pll_div1 & MG_PLL_DIV1_FBPREDIV_MASK;
	m2_int = pll_state->mg_pll_div0 & MG_PLL_DIV0_FBDIV_INT_MASK;
	m2_frac = (pll_state->mg_pll_div0 & MG_PLL_DIV0_FRACNEN_H) ?
		(pll_state->mg_pll_div0 & MG_PLL_DIV0_FBDIV_FRAC_MASK) >>
		MG_PLL_DIV0_FBDIV_FRAC_SHIFT : 0;

	switch (pll_state->mg_clktop2_hsclkctl &
		MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_MASK) {
	case MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_2:
		div1 = 2;
		break;
	case MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_3:
		div1 = 3;
		break;
	case MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_5:
		div1 = 5;
		break;
	case MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_7:
		div1 = 7;
		break;
	default:
		MISSING_CASE(pll_state->mg_clktop2_hsclkctl);
		return 0;
	}

	div2 = (pll_state->mg_clktop2_hsclkctl &
		MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO_MASK) >>
		MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO_SHIFT;

	/* div2 value of 0 is same as 1 means no div */
	if (div2 == 0)
		div2 = 1;

	/*
	 * Adjust the original formula to delay the division by 2^22 in order to
	 * minimize possible rounding errors.
	 */
	tmp = (u64)m1 * m2_int * ref_clock +
	      (((u64)m1 * m2_frac * ref_clock) >> 22);
	tmp = div_u64(tmp, 5 * div1 * div2);

	return tmp;
}