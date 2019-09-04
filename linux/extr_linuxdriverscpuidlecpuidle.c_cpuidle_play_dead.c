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
struct cpuidle_driver {int state_count; TYPE_1__* states; } ;
struct cpuidle_device {int dummy; } ;
struct TYPE_2__ {int (* enter_dead ) (struct cpuidle_device*,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 struct cpuidle_device* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuidle_devices ; 
 struct cpuidle_driver* cpuidle_get_cpu_driver (struct cpuidle_device*) ; 
 int stub1 (struct cpuidle_device*,int) ; 

int cpuidle_play_dead(void)
{
	struct cpuidle_device *dev = __this_cpu_read(cpuidle_devices);
	struct cpuidle_driver *drv = cpuidle_get_cpu_driver(dev);
	int i;

	if (!drv)
		return -ENODEV;

	/* Find lowest-power state that supports long-term idle */
	for (i = drv->state_count - 1; i >= 0; i--)
		if (drv->states[i].enter_dead)
			return drv->states[i].enter_dead(dev, i);

	return -ENODEV;
}