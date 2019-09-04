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
struct cpuidle_driver {scalar_t__ refcnt; int /*<<< orphan*/  cpumask; scalar_t__ bctimer; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __cpuidle_unset_driver (struct cpuidle_driver*) ; 
 int /*<<< orphan*/  cpuidle_setup_broadcast_timer ; 
 int /*<<< orphan*/  on_each_cpu_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void __cpuidle_unregister_driver(struct cpuidle_driver *drv)
{
	if (WARN_ON(drv->refcnt > 0))
		return;

	if (drv->bctimer) {
		drv->bctimer = 0;
		on_each_cpu_mask(drv->cpumask, cpuidle_setup_broadcast_timer,
				 NULL, 1);
	}

	__cpuidle_unset_driver(drv);
}