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
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  calxeda_idle_finish ; 
 int /*<<< orphan*/  cpu_pm_enter () ; 
 int /*<<< orphan*/  cpu_pm_exit () ; 
 int /*<<< orphan*/  cpu_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int calxeda_pwrdown_idle(struct cpuidle_device *dev,
				struct cpuidle_driver *drv,
				int index)
{
	cpu_pm_enter();
	cpu_suspend(0, calxeda_idle_finish);
	cpu_pm_exit();

	return index;
}