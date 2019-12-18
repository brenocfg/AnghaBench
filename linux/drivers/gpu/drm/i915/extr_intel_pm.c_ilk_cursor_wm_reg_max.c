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

__attribute__((used)) static unsigned int
ilk_cursor_wm_reg_max(const struct drm_i915_private *dev_priv, int level)
{
	if (INTEL_GEN(dev_priv) >= 7)
		return level == 0 ? 63 : 255;
	else
		return level == 0 ? 31 : 63;
}