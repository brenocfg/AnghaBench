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
typedef  int /*<<< orphan*/  u64 ;
struct i915_power_domains {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __async_put_domains_mask (struct i915_power_domains*) ; 
 int /*<<< orphan*/  assert_async_put_domain_masks_disjoint (struct i915_power_domains*) ; 

__attribute__((used)) static u64 async_put_domains_mask(struct i915_power_domains *power_domains)
{
	assert_async_put_domain_masks_disjoint(power_domains);

	return __async_put_domains_mask(power_domains);
}