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
struct i915_power_domains {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; struct i915_power_domains power_domains; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_display_power_get_domain (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

intel_wakeref_t intel_display_power_get(struct drm_i915_private *dev_priv,
					enum intel_display_power_domain domain)
{
	struct i915_power_domains *power_domains = &dev_priv->power_domains;
	intel_wakeref_t wakeref = intel_runtime_pm_get(&dev_priv->runtime_pm);

	mutex_lock(&power_domains->lock);
	__intel_display_power_get_domain(dev_priv, domain);
	mutex_unlock(&power_domains->lock);

	return wakeref;
}