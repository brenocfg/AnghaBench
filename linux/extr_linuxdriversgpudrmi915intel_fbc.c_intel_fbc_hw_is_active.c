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
 scalar_t__ IS_GM45 (struct drm_i915_private*) ; 
 int g4x_fbc_is_active (struct drm_i915_private*) ; 
 int i8xx_fbc_is_active (struct drm_i915_private*) ; 
 int ilk_fbc_is_active (struct drm_i915_private*) ; 

__attribute__((used)) static bool intel_fbc_hw_is_active(struct drm_i915_private *dev_priv)
{
	if (INTEL_GEN(dev_priv) >= 5)
		return ilk_fbc_is_active(dev_priv);
	else if (IS_GM45(dev_priv))
		return g4x_fbc_is_active(dev_priv);
	else
		return i8xx_fbc_is_active(dev_priv);
}