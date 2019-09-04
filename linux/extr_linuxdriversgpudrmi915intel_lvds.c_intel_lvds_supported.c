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
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_I830 (struct drm_i915_private*) ; 
 scalar_t__ IS_MOBILE (struct drm_i915_private*) ; 

__attribute__((used)) static bool intel_lvds_supported(struct drm_i915_private *dev_priv)
{
	/*
	 * With the introduction of the PCH we gained a dedicated
	 * LVDS presence pin, use it.
	 */
	if (HAS_PCH_IBX(dev_priv) || HAS_PCH_CPT(dev_priv))
		return true;

	/*
	 * Otherwise LVDS was only attached to mobile products,
	 * except for the inglorious 830gm
	 */
	if (INTEL_GEN(dev_priv) <= 4 &&
	    IS_MOBILE(dev_priv) && !IS_I830(dev_priv))
		return true;

	return false;
}