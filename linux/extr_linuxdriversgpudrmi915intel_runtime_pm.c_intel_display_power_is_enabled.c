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
struct drm_i915_private {struct i915_power_domains power_domains; } ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 int __intel_display_power_is_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

bool intel_display_power_is_enabled(struct drm_i915_private *dev_priv,
				    enum intel_display_power_domain domain)
{
	struct i915_power_domains *power_domains;
	bool ret;

	power_domains = &dev_priv->power_domains;

	mutex_lock(&power_domains->lock);
	ret = __intel_display_power_is_enabled(dev_priv, domain);
	mutex_unlock(&power_domains->lock);

	return ret;
}