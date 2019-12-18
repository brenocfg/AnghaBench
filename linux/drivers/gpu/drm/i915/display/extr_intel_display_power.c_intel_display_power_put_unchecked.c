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
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; } ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_display_power_put (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_runtime_pm_put_unchecked (int /*<<< orphan*/ *) ; 

void intel_display_power_put_unchecked(struct drm_i915_private *dev_priv,
				       enum intel_display_power_domain domain)
{
	__intel_display_power_put(dev_priv, domain);
	intel_runtime_pm_put_unchecked(&dev_priv->runtime_pm);
}