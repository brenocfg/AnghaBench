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
struct cpuidle_device {scalar_t__ registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cpuidle_unregister_device (struct cpuidle_device*) ; 
 int /*<<< orphan*/  cpuidle_coupled_unregister_device (struct cpuidle_device*) ; 
 int /*<<< orphan*/  cpuidle_disable_device (struct cpuidle_device*) ; 
 int /*<<< orphan*/  cpuidle_pause_and_lock () ; 
 int /*<<< orphan*/  cpuidle_remove_sysfs (struct cpuidle_device*) ; 
 int /*<<< orphan*/  cpuidle_resume_and_unlock () ; 

void cpuidle_unregister_device(struct cpuidle_device *dev)
{
	if (!dev || dev->registered == 0)
		return;

	cpuidle_pause_and_lock();

	cpuidle_disable_device(dev);

	cpuidle_remove_sysfs(dev);

	__cpuidle_unregister_device(dev);

	cpuidle_coupled_unregister_device(dev);

	cpuidle_resume_and_unlock();
}