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
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 struct device* get_cpu_device (unsigned int) ; 
 int /*<<< orphan*/  mc_attr_group ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mc_cpu_down_prep(unsigned int cpu)
{
	struct device *dev;

	dev = get_cpu_device(cpu);
	/* Suspend is in progress, only remove the interface */
	sysfs_remove_group(&dev->kobj, &mc_attr_group);
	pr_debug("CPU%d removed\n", cpu);

	return 0;
}