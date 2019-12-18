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

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int LCPLL_CD_SOURCE_FCLK ; 
 int /*<<< orphan*/  LCPLL_CTL ; 
 int LCPLL_PLL_DISABLE ; 
 int LCPLL_REF_MASK ; 
 int LCPLL_REF_NON_SSC ; 

__attribute__((used)) static void hsw_assert_cdclk(struct drm_i915_private *dev_priv)
{
	u32 val = I915_READ(LCPLL_CTL);

	/*
	 * The LCPLL register should be turned on by the BIOS. For now
	 * let's just check its state and print errors in case
	 * something is wrong.  Don't even try to turn it on.
	 */

	if (val & LCPLL_CD_SOURCE_FCLK)
		DRM_ERROR("CDCLK source is not LCPLL\n");

	if (val & LCPLL_PLL_DISABLE)
		DRM_ERROR("LCPLL is disabled\n");

	if ((val & LCPLL_REF_MASK) != LCPLL_REF_NON_SSC)
		DRM_ERROR("LCPLL not using non-SSC reference\n");
}