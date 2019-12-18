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
struct i915_power_domains {int async_put_wakeref; int /*<<< orphan*/  async_put_work; } ;
typedef  int intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_unbound_wq ; 

__attribute__((used)) static void
queue_async_put_domains_work(struct i915_power_domains *power_domains,
			     intel_wakeref_t wakeref)
{
	WARN_ON(power_domains->async_put_wakeref);
	power_domains->async_put_wakeref = wakeref;
	WARN_ON(!queue_delayed_work(system_unbound_wq,
				    &power_domains->async_put_work,
				    msecs_to_jiffies(100)));
}