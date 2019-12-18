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
 int /*<<< orphan*/  intel_gvt_active (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gvt_clean_device (struct drm_i915_private*) ; 

void intel_gvt_driver_remove(struct drm_i915_private *dev_priv)
{
	if (!intel_gvt_active(dev_priv))
		return;

	intel_gvt_clean_device(dev_priv);
}