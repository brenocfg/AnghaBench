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
 int /*<<< orphan*/  BXT_DE_PLL_ENABLE ; 
 int /*<<< orphan*/  BXT_DE_PLL_LOCK ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bxt_de_pll_disable(struct drm_i915_private *dev_priv)
{
	I915_WRITE(BXT_DE_PLL_ENABLE, 0);

	/* Timeout 200us */
	if (intel_de_wait_for_clear(dev_priv,
				    BXT_DE_PLL_ENABLE, BXT_DE_PLL_LOCK, 1))
		DRM_ERROR("timeout waiting for DE PLL unlock\n");

	dev_priv->cdclk.hw.vco = 0;
}