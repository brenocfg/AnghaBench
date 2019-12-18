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
struct drm_i915_private {int hpll_freq; } ;

/* Variables and functions */
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 

__attribute__((used)) static int vlv_calc_cdclk(struct drm_i915_private *dev_priv, int min_cdclk)
{
	int freq_320 = (dev_priv->hpll_freq <<  1) % 320000 != 0 ?
		333333 : 320000;

	/*
	 * We seem to get an unstable or solid color picture at 200MHz.
	 * Not sure what's wrong. For now use 200MHz only when all pipes
	 * are off.
	 */
	if (IS_VALLEYVIEW(dev_priv) && min_cdclk > freq_320)
		return 400000;
	else if (min_cdclk > 266667)
		return freq_320;
	else if (min_cdclk > 0)
		return 266667;
	else
		return 200000;
}