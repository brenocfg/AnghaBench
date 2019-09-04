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
struct cpuidle_driver {int /*<<< orphan*/  cpumask; scalar_t__ bctimer; int /*<<< orphan*/  state_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  __cpuidle_driver_init (struct cpuidle_driver*) ; 
 int __cpuidle_set_driver (struct cpuidle_driver*) ; 
 int cpuidle_coupled_state_verify (struct cpuidle_driver*) ; 
 scalar_t__ cpuidle_disabled () ; 
 int /*<<< orphan*/  cpuidle_setup_broadcast_timer ; 
 int /*<<< orphan*/  on_each_cpu_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int __cpuidle_register_driver(struct cpuidle_driver *drv)
{
	int ret;

	if (!drv || !drv->state_count)
		return -EINVAL;

	ret = cpuidle_coupled_state_verify(drv);
	if (ret)
		return ret;

	if (cpuidle_disabled())
		return -ENODEV;

	__cpuidle_driver_init(drv);

	ret = __cpuidle_set_driver(drv);
	if (ret)
		return ret;

	if (drv->bctimer)
		on_each_cpu_mask(drv->cpumask, cpuidle_setup_broadcast_timer,
				 (void *)1, 1);

	return 0;
}