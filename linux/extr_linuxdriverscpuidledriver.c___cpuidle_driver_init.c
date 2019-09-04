#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpumask {int dummy; } ;
struct cpuidle_driver {int state_count; int bctimer; TYPE_1__* states; struct cpumask* cpumask; scalar_t__ refcnt; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CPUIDLE_FLAG_TIMER_STOP ; 
 scalar_t__ cpu_possible_mask ; 

__attribute__((used)) static void __cpuidle_driver_init(struct cpuidle_driver *drv)
{
	int i;

	drv->refcnt = 0;

	/*
	 * Use all possible CPUs as the default, because if the kernel boots
	 * with some CPUs offline and then we online one of them, the CPU
	 * notifier has to know which driver to assign.
	 */
	if (!drv->cpumask)
		drv->cpumask = (struct cpumask *)cpu_possible_mask;

	/*
	 * Look for the timer stop flag in the different states, so that we know
	 * if the broadcast timer has to be set up.  The loop is in the reverse
	 * order, because usually one of the deeper states have this flag set.
	 */
	for (i = drv->state_count - 1; i >= 0 ; i--) {
		if (drv->states[i].flags & CPUIDLE_FLAG_TIMER_STOP) {
			drv->bctimer = 1;
			break;
		}
	}
}