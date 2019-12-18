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
struct intel_runtime_pm {int dummy; } ;
struct i915_power_domains {int* domain_use_count; int /*<<< orphan*/  lock; int /*<<< orphan*/ * async_put_domains; scalar_t__ async_put_wakeref; } ;
struct drm_i915_private {struct intel_runtime_pm runtime_pm; struct i915_power_domains power_domains; } ;
typedef  scalar_t__ intel_wakeref_t ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __intel_display_power_put_domain (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  fetch_and_zero (scalar_t__*) ; 
 scalar_t__ intel_runtime_pm_get_raw (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct intel_runtime_pm*,scalar_t__) ; 
 int /*<<< orphan*/  intel_runtime_pm_put_raw (struct intel_runtime_pm*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_async_put_domains_work (struct i915_power_domains*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_async_put_domains_state (struct i915_power_domains*) ; 

void __intel_display_power_put_async(struct drm_i915_private *i915,
				     enum intel_display_power_domain domain,
				     intel_wakeref_t wakeref)
{
	struct i915_power_domains *power_domains = &i915->power_domains;
	struct intel_runtime_pm *rpm = &i915->runtime_pm;
	intel_wakeref_t work_wakeref = intel_runtime_pm_get_raw(rpm);

	mutex_lock(&power_domains->lock);

	if (power_domains->domain_use_count[domain] > 1) {
		__intel_display_power_put_domain(i915, domain);

		goto out_verify;
	}

	WARN_ON(power_domains->domain_use_count[domain] != 1);

	/* Let a pending work requeue itself or queue a new one. */
	if (power_domains->async_put_wakeref) {
		power_domains->async_put_domains[1] |= BIT_ULL(domain);
	} else {
		power_domains->async_put_domains[0] |= BIT_ULL(domain);
		queue_async_put_domains_work(power_domains,
					     fetch_and_zero(&work_wakeref));
	}

out_verify:
	verify_async_put_domains_state(power_domains);

	mutex_unlock(&power_domains->lock);

	if (work_wakeref)
		intel_runtime_pm_put_raw(rpm, work_wakeref);

	intel_runtime_pm_put(rpm, wakeref);
}