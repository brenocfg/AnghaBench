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
struct TYPE_3__ {scalar_t__ vco; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
struct drm_i915_private {TYPE_2__ cdclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LCPLL1_CTL ; 
 int LCPLL_PLL_ENABLE ; 
 int /*<<< orphan*/  LCPLL_PLL_LOCK ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void skl_dpll0_disable(struct drm_i915_private *dev_priv)
{
	I915_WRITE(LCPLL1_CTL, I915_READ(LCPLL1_CTL) & ~LCPLL_PLL_ENABLE);
	if (intel_de_wait_for_clear(dev_priv, LCPLL1_CTL, LCPLL_PLL_LOCK, 1))
		DRM_ERROR("Couldn't disable DPLL0\n");

	dev_priv->cdclk.hw.vco = 0;
}