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
 int /*<<< orphan*/  FUSE_STRAP3 ; 
 int HSW_REF_CLK_SELECT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_HSW_ULT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int WRPLL_DIVIDER_FB_MASK ; 
 int WRPLL_DIVIDER_FB_SHIFT ; 
 int WRPLL_DIVIDER_POST_MASK ; 
 int WRPLL_DIVIDER_POST_SHIFT ; 
 int WRPLL_DIVIDER_REF_MASK ; 
#define  WRPLL_REF_LCPLL 130 
 int WRPLL_REF_MASK ; 
#define  WRPLL_REF_PCH_SSC 129 
#define  WRPLL_REF_SPECIAL_HSW 128 

__attribute__((used)) static int hsw_ddi_calc_wrpll_link(struct drm_i915_private *dev_priv,
				   i915_reg_t reg)
{
	int refclk;
	int n, p, r;
	u32 wrpll;

	wrpll = I915_READ(reg);
	switch (wrpll & WRPLL_REF_MASK) {
	case WRPLL_REF_SPECIAL_HSW:
		/*
		 * muxed-SSC for BDW.
		 * non-SSC for non-ULT HSW. Check FUSE_STRAP3
		 * for the non-SSC reference frequency.
		 */
		if (IS_HASWELL(dev_priv) && !IS_HSW_ULT(dev_priv)) {
			if (I915_READ(FUSE_STRAP3) & HSW_REF_CLK_SELECT)
				refclk = 24;
			else
				refclk = 135;
			break;
		}
		/* fall through */
	case WRPLL_REF_PCH_SSC:
		/*
		 * We could calculate spread here, but our checking
		 * code only cares about 5% accuracy, and spread is a max of
		 * 0.5% downspread.
		 */
		refclk = 135;
		break;
	case WRPLL_REF_LCPLL:
		refclk = 2700;
		break;
	default:
		MISSING_CASE(wrpll);
		return 0;
	}

	r = wrpll & WRPLL_DIVIDER_REF_MASK;
	p = (wrpll & WRPLL_DIVIDER_POST_MASK) >> WRPLL_DIVIDER_POST_SHIFT;
	n = (wrpll & WRPLL_DIVIDER_FB_MASK) >> WRPLL_DIVIDER_FB_SHIFT;

	/* Convert to KHz, p & r have a fixed point portion */
	return (refclk * n * 100) / (p * r);
}