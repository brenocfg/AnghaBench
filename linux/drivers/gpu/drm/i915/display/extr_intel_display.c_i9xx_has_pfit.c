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
 scalar_t__ IS_I830 (struct drm_i915_private*) ; 
 scalar_t__ IS_MOBILE (struct drm_i915_private*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 

__attribute__((used)) static bool i9xx_has_pfit(struct drm_i915_private *dev_priv)
{
	if (IS_I830(dev_priv))
		return false;

	return INTEL_GEN(dev_priv) >= 4 ||
		IS_PINEVIEW(dev_priv) || IS_MOBILE(dev_priv);
}