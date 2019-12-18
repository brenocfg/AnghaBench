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
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 

__attribute__((used)) static bool skl_wm_has_lines(struct drm_i915_private *dev_priv, int level)
{
	if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv))
		return true;

	/* The number of lines are ignored for the level 0 watermark. */
	return level > 0;
}