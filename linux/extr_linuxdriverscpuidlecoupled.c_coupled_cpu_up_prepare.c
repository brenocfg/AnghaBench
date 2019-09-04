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
struct cpuidle_device {scalar_t__ coupled; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuidle_coupled_prevent_idle (scalar_t__) ; 
 int /*<<< orphan*/  cpuidle_devices ; 
 int /*<<< orphan*/  cpuidle_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cpuidle_device* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int coupled_cpu_up_prepare(unsigned int cpu)
{
	struct cpuidle_device *dev;

	mutex_lock(&cpuidle_lock);

	dev = per_cpu(cpuidle_devices, cpu);
	if (dev && dev->coupled)
		cpuidle_coupled_prevent_idle(dev->coupled);

	mutex_unlock(&cpuidle_lock);
	return 0;
}