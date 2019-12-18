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
struct i915_power_domains {int /*<<< orphan*/  lock; int /*<<< orphan*/  async_put_work; int /*<<< orphan*/  async_put_wakeref; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; struct i915_power_domains power_domains; } ;
typedef  scalar_t__ intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  async_put_domains_mask (struct i915_power_domains*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 scalar_t__ fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put_raw (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_async_put_domains (struct i915_power_domains*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_async_put_domains_state (struct i915_power_domains*) ; 

void intel_display_power_flush_work(struct drm_i915_private *i915)
{
	struct i915_power_domains *power_domains = &i915->power_domains;
	intel_wakeref_t work_wakeref;

	mutex_lock(&power_domains->lock);

	work_wakeref = fetch_and_zero(&power_domains->async_put_wakeref);
	if (!work_wakeref)
		goto out_verify;

	release_async_put_domains(power_domains,
				  async_put_domains_mask(power_domains));
	cancel_delayed_work(&power_domains->async_put_work);

out_verify:
	verify_async_put_domains_state(power_domains);

	mutex_unlock(&power_domains->lock);

	if (work_wakeref)
		intel_runtime_pm_put_raw(&i915->runtime_pm, work_wakeref);
}