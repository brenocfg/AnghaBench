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
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 

__attribute__((used)) static bool is_supported_device(struct drm_i915_private *dev_priv)
{
	if (IS_BROADWELL(dev_priv))
		return true;
	if (IS_SKYLAKE(dev_priv))
		return true;
	if (IS_KABYLAKE(dev_priv))
		return true;
	if (IS_BROXTON(dev_priv))
		return true;
	if (IS_COFFEELAKE(dev_priv))
		return true;

	return false;
}