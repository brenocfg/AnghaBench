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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private const*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private const*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private const*) ; 

int ilk_wm_max_level(const struct drm_i915_private *dev_priv)
{
	/* how many WM levels are we expecting */
	if (INTEL_GEN(dev_priv) >= 9)
		return 7;
	else if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		return 4;
	else if (INTEL_GEN(dev_priv) >= 6)
		return 3;
	else
		return 2;
}