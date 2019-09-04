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
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuidle_devices ; 
 int /*<<< orphan*/  cpuidle_disable_device (struct cpuidle_device*) ; 
 scalar_t__ cpuidle_get_driver () ; 
 int /*<<< orphan*/  cpuidle_pause_and_lock () ; 
 int /*<<< orphan*/  cpuidle_resume_and_unlock () ; 
 struct cpuidle_device* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pseries_cpuidle_cpu_dead(unsigned int cpu)
{
	struct cpuidle_device *dev = per_cpu(cpuidle_devices, cpu);

	if (dev && cpuidle_get_driver()) {
		cpuidle_pause_and_lock();
		cpuidle_disable_device(dev);
		cpuidle_resume_and_unlock();
	}
	return 0;
}