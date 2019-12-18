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
struct temp_data {unsigned int cpu; int /*<<< orphan*/  update_lock; } ;
struct platform_device {int dummy; } ;
struct platform_data {int /*<<< orphan*/  cpumask; struct temp_data** core_data; } ;

/* Variables and functions */
 int MAX_CORE_DATA ; 
 size_t PKG_SYSFS_ATTR_NO ; 
 int TO_ATTR_NO (unsigned int) ; 
 struct platform_device* coretemp_get_pdev (unsigned int) ; 
 int /*<<< orphan*/  coretemp_remove_core (struct platform_data*,int) ; 
 scalar_t__ cpuhp_tasks_frozen ; 
 int cpumask_any_and (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 
 int cpumask_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 struct platform_data* platform_get_drvdata (struct platform_device*) ; 
 size_t topology_logical_die_id (unsigned int) ; 
 int /*<<< orphan*/  topology_sibling_cpumask (unsigned int) ; 
 int /*<<< orphan*/ ** zone_devices ; 

__attribute__((used)) static int coretemp_cpu_offline(unsigned int cpu)
{
	struct platform_device *pdev = coretemp_get_pdev(cpu);
	struct platform_data *pd;
	struct temp_data *tdata;
	int indx, target;

	/*
	 * Don't execute this on suspend as the device remove locks
	 * up the machine.
	 */
	if (cpuhp_tasks_frozen)
		return 0;

	/* If the physical CPU device does not exist, just return */
	if (!pdev)
		return 0;

	/* The core id is too big, just return */
	indx = TO_ATTR_NO(cpu);
	if (indx > MAX_CORE_DATA - 1)
		return 0;

	pd = platform_get_drvdata(pdev);
	tdata = pd->core_data[indx];

	cpumask_clear_cpu(cpu, &pd->cpumask);

	/*
	 * If this is the last thread sibling, remove the CPU core
	 * interface, If there is still a sibling online, transfer the
	 * target cpu of that core interface to it.
	 */
	target = cpumask_any_and(&pd->cpumask, topology_sibling_cpumask(cpu));
	if (target >= nr_cpu_ids) {
		coretemp_remove_core(pd, indx);
	} else if (tdata && tdata->cpu == cpu) {
		mutex_lock(&tdata->update_lock);
		tdata->cpu = target;
		mutex_unlock(&tdata->update_lock);
	}

	/*
	 * If all cores in this pkg are offline, remove the device. This
	 * will invoke the platform driver remove function, which cleans up
	 * the rest.
	 */
	if (cpumask_empty(&pd->cpumask)) {
		zone_devices[topology_logical_die_id(cpu)] = NULL;
		platform_device_unregister(pdev);
		return 0;
	}

	/*
	 * Check whether this core is the target for the package
	 * interface. We need to assign it to some other cpu.
	 */
	tdata = pd->core_data[PKG_SYSFS_ATTR_NO];
	if (tdata && tdata->cpu == cpu) {
		target = cpumask_first(&pd->cpumask);
		mutex_lock(&tdata->update_lock);
		tdata->cpu = target;
		mutex_unlock(&tdata->update_lock);
	}
	return 0;
}