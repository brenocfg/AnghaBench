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
struct i915_power_domains {int /*<<< orphan*/  async_put_wakeref; int /*<<< orphan*/  async_put_work; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; struct i915_power_domains power_domains; } ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  async_put_domains_clear_domain (struct i915_power_domains*,int) ; 
 int async_put_domains_mask (struct i915_power_domains*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put_raw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_async_put_domains_state (struct i915_power_domains*) ; 

__attribute__((used)) static bool
intel_display_power_grab_async_put_ref(struct drm_i915_private *dev_priv,
				       enum intel_display_power_domain domain)
{
	struct i915_power_domains *power_domains = &dev_priv->power_domains;
	bool ret = false;

	if (!(async_put_domains_mask(power_domains) & BIT_ULL(domain)))
		goto out_verify;

	async_put_domains_clear_domain(power_domains, domain);

	ret = true;

	if (async_put_domains_mask(power_domains))
		goto out_verify;

	cancel_delayed_work(&power_domains->async_put_work);
	intel_runtime_pm_put_raw(&dev_priv->runtime_pm,
				 fetch_and_zero(&power_domains->async_put_wakeref));
out_verify:
	verify_async_put_domains_state(power_domains);

	return ret;
}