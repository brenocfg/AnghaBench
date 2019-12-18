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
typedef  int u8 ;
struct drm_i915_private {int hpll_freq; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 

__attribute__((used)) static u8 vlv_calc_voltage_level(struct drm_i915_private *dev_priv, int cdclk)
{
	if (IS_VALLEYVIEW(dev_priv)) {
		if (cdclk >= 320000) /* jump to highest voltage for 400MHz too */
			return 2;
		else if (cdclk >= 266667)
			return 1;
		else
			return 0;
	} else {
		/*
		 * Specs are full of misinformation, but testing on actual
		 * hardware has shown that we just need to write the desired
		 * CCK divider into the Punit register.
		 */
		return DIV_ROUND_CLOSEST(dev_priv->hpll_freq << 1, cdclk) - 1;
	}
}