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

__attribute__((used)) static unsigned int ilk_fbc_wm_reg_max(const struct drm_i915_private *dev_priv)
{
	if (INTEL_GEN(dev_priv) >= 8)
		return 31;
	else
		return 15;
}