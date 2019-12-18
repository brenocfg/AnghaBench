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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int vco; int /*<<< orphan*/  ref; } ;
struct TYPE_3__ {TYPE_2__ hw; } ;
struct drm_i915_private {TYPE_1__ cdclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_DE_PLL_CTL ; 
 int /*<<< orphan*/  BXT_DE_PLL_ENABLE ; 
 int /*<<< orphan*/  BXT_DE_PLL_LOCK ; 
 int /*<<< orphan*/  BXT_DE_PLL_PLL_ENABLE ; 
 int /*<<< orphan*/  BXT_DE_PLL_RATIO (int) ; 
 int /*<<< orphan*/  BXT_DE_PLL_RATIO_MASK ; 
 int DIV_ROUND_CLOSEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_de_wait_for_set (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bxt_de_pll_enable(struct drm_i915_private *dev_priv, int vco)
{
	int ratio = DIV_ROUND_CLOSEST(vco, dev_priv->cdclk.hw.ref);
	u32 val;

	val = I915_READ(BXT_DE_PLL_CTL);
	val &= ~BXT_DE_PLL_RATIO_MASK;
	val |= BXT_DE_PLL_RATIO(ratio);
	I915_WRITE(BXT_DE_PLL_CTL, val);

	I915_WRITE(BXT_DE_PLL_ENABLE, BXT_DE_PLL_PLL_ENABLE);

	/* Timeout 200us */
	if (intel_de_wait_for_set(dev_priv,
				  BXT_DE_PLL_ENABLE, BXT_DE_PLL_LOCK, 1))
		DRM_ERROR("timeout waiting for DE PLL lock\n");

	dev_priv->cdclk.hw.vco = vco;
}