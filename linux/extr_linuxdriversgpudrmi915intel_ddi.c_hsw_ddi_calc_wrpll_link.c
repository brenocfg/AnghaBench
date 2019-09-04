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
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int LC_FREQ ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int WRPLL_DIVIDER_FB_MASK ; 
 int WRPLL_DIVIDER_FB_SHIFT ; 
 int WRPLL_DIVIDER_POST_MASK ; 
 int WRPLL_DIVIDER_POST_SHIFT ; 
 int WRPLL_DIVIDER_REF_MASK ; 
#define  WRPLL_PLL_LCPLL 130 
#define  WRPLL_PLL_NON_SSC 129 
 int WRPLL_PLL_REF_MASK ; 
#define  WRPLL_PLL_SSC 128 

__attribute__((used)) static int hsw_ddi_calc_wrpll_link(struct drm_i915_private *dev_priv,
				   i915_reg_t reg)
{
	int refclk = LC_FREQ;
	int n, p, r;
	u32 wrpll;

	wrpll = I915_READ(reg);
	switch (wrpll & WRPLL_PLL_REF_MASK) {
	case WRPLL_PLL_SSC:
	case WRPLL_PLL_NON_SSC:
		/*
		 * We could calculate spread here, but our checking
		 * code only cares about 5% accuracy, and spread is a max of
		 * 0.5% downspread.
		 */
		refclk = 135;
		break;
	case WRPLL_PLL_LCPLL:
		refclk = LC_FREQ;
		break;
	default:
		WARN(1, "bad wrpll refclk\n");
		return 0;
	}

	r = wrpll & WRPLL_DIVIDER_REF_MASK;
	p = (wrpll & WRPLL_DIVIDER_POST_MASK) >> WRPLL_DIVIDER_POST_SHIFT;
	n = (wrpll & WRPLL_DIVIDER_FB_MASK) >> WRPLL_DIVIDER_FB_SHIFT;

	/* Convert to KHz, p & r have a fixed point portion */
	return (refclk * n * 100) / (p * r);
}