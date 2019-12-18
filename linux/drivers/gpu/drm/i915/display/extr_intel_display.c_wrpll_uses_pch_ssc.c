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
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_STRAP ; 
 int HSW_CPU_SSC_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HSW_ULT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WRPLL_CTL (int) ; 
 int WRPLL_PLL_ENABLE ; 
 int WRPLL_REF_MASK ; 
 int WRPLL_REF_MUXED_SSC_BDW ; 
 int WRPLL_REF_PCH_SSC ; 

__attribute__((used)) static bool wrpll_uses_pch_ssc(struct drm_i915_private *dev_priv,
			       enum intel_dpll_id id)
{
	u32 fuse_strap = I915_READ(FUSE_STRAP);
	u32 ctl = I915_READ(WRPLL_CTL(id));

	if ((ctl & WRPLL_PLL_ENABLE) == 0)
		return false;

	if ((ctl & WRPLL_REF_MASK) == WRPLL_REF_PCH_SSC)
		return true;

	if ((IS_BROADWELL(dev_priv) || IS_HSW_ULT(dev_priv)) &&
	    (ctl & WRPLL_REF_MASK) == WRPLL_REF_MUXED_SSC_BDW &&
	    (fuse_strap & HSW_CPU_SSC_ENABLE) == 0)
		return true;

	return false;
}