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
struct drm_i915_private {struct i915_power_domains power_domains; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_display_power_flush_work (struct drm_i915_private*) ; 
 int /*<<< orphan*/  verify_async_put_domains_state (struct i915_power_domains*) ; 

__attribute__((used)) static void
intel_display_power_flush_work_sync(struct drm_i915_private *i915)
{
	struct i915_power_domains *power_domains = &i915->power_domains;

	intel_display_power_flush_work(i915);
	cancel_delayed_work_sync(&power_domains->async_put_work);

	verify_async_put_domains_state(power_domains);

	WARN_ON(power_domains->async_put_wakeref);
}