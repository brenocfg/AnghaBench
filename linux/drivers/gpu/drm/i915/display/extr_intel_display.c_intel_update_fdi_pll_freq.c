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
struct drm_i915_private {int fdi_pll_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  FDI_PLL_BIOS_0 ; 
 int FDI_PLL_FB_CLOCK_MASK ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 

__attribute__((used)) static void intel_update_fdi_pll_freq(struct drm_i915_private *dev_priv)
{
	if (IS_GEN(dev_priv, 5)) {
		u32 fdi_pll_clk =
			I915_READ(FDI_PLL_BIOS_0) & FDI_PLL_FB_CLOCK_MASK;

		dev_priv->fdi_pll_freq = (fdi_pll_clk + 2) * 10000;
	} else if (IS_GEN(dev_priv, 6) || IS_IVYBRIDGE(dev_priv)) {
		dev_priv->fdi_pll_freq = 270000;
	} else {
		return;
	}

	DRM_DEBUG_DRIVER("FDI PLL freq=%d\n", dev_priv->fdi_pll_freq);
}