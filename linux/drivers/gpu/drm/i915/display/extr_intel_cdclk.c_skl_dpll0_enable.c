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
typedef  int u32 ;
struct TYPE_3__ {int vco; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
struct drm_i915_private {TYPE_2__ cdclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL_CTRL1 ; 
 int DPLL_CTRL1_HDMI_MODE (int /*<<< orphan*/ ) ; 
 int DPLL_CTRL1_LINK_RATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPLL_CTRL1_LINK_RATE_1080 ; 
 int /*<<< orphan*/  DPLL_CTRL1_LINK_RATE_810 ; 
 int DPLL_CTRL1_LINK_RATE_MASK (int /*<<< orphan*/ ) ; 
 int DPLL_CTRL1_OVERRIDE (int /*<<< orphan*/ ) ; 
 int DPLL_CTRL1_SSC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LCPLL1_CTL ; 
 int LCPLL_PLL_ENABLE ; 
 int /*<<< orphan*/  LCPLL_PLL_LOCK ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKL_DPLL0 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ intel_de_wait_for_set (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skl_set_preferred_cdclk_vco (struct drm_i915_private*,int) ; 

__attribute__((used)) static void skl_dpll0_enable(struct drm_i915_private *dev_priv, int vco)
{
	u32 val;

	WARN_ON(vco != 8100000 && vco != 8640000);

	/*
	 * We always enable DPLL0 with the lowest link rate possible, but still
	 * taking into account the VCO required to operate the eDP panel at the
	 * desired frequency. The usual DP link rates operate with a VCO of
	 * 8100 while the eDP 1.4 alternate link rates need a VCO of 8640.
	 * The modeset code is responsible for the selection of the exact link
	 * rate later on, with the constraint of choosing a frequency that
	 * works with vco.
	 */
	val = I915_READ(DPLL_CTRL1);

	val &= ~(DPLL_CTRL1_HDMI_MODE(SKL_DPLL0) | DPLL_CTRL1_SSC(SKL_DPLL0) |
		 DPLL_CTRL1_LINK_RATE_MASK(SKL_DPLL0));
	val |= DPLL_CTRL1_OVERRIDE(SKL_DPLL0);
	if (vco == 8640000)
		val |= DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_1080,
					    SKL_DPLL0);
	else
		val |= DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_810,
					    SKL_DPLL0);

	I915_WRITE(DPLL_CTRL1, val);
	POSTING_READ(DPLL_CTRL1);

	I915_WRITE(LCPLL1_CTL, I915_READ(LCPLL1_CTL) | LCPLL_PLL_ENABLE);

	if (intel_de_wait_for_set(dev_priv, LCPLL1_CTL, LCPLL_PLL_LOCK, 5))
		DRM_ERROR("DPLL0 not locked\n");

	dev_priv->cdclk.hw.vco = vco;

	/* We'll want to keep using the current vco from now on. */
	skl_set_preferred_cdclk_vco(dev_priv, vco);
}