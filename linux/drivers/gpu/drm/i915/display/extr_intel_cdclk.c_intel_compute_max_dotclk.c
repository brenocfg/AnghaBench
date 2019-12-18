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
struct drm_i915_private {int max_cdclk_freq; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 

__attribute__((used)) static int intel_compute_max_dotclk(struct drm_i915_private *dev_priv)
{
	int max_cdclk_freq = dev_priv->max_cdclk_freq;

	if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv))
		return 2 * max_cdclk_freq;
	else if (IS_GEN(dev_priv, 9) ||
		 IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv))
		return max_cdclk_freq;
	else if (IS_CHERRYVIEW(dev_priv))
		return max_cdclk_freq*95/100;
	else if (INTEL_GEN(dev_priv) < 4)
		return 2*max_cdclk_freq*90/100;
	else
		return max_cdclk_freq*90/100;
}