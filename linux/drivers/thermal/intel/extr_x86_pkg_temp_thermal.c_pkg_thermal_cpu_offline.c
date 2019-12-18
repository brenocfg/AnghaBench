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
struct zone_device {unsigned int cpu; int /*<<< orphan*/  work; scalar_t__ work_scheduled; int /*<<< orphan*/  msr_pkg_therm_high; int /*<<< orphan*/  msr_pkg_therm_low; struct thermal_zone_device* tzone; int /*<<< orphan*/  cpumask; } ;
struct thermal_zone_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_PACKAGE_THERM_INTERRUPT ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int cpumask_any_but (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct zone_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  pkg_temp_lock ; 
 struct zone_device* pkg_temp_thermal_get_dev (unsigned int) ; 
 int /*<<< orphan*/  pkg_thermal_schedule_work (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  thermal_zone_mutex ; 
 size_t topology_logical_die_id (unsigned int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** zones ; 

__attribute__((used)) static int pkg_thermal_cpu_offline(unsigned int cpu)
{
	struct zone_device *zonedev = pkg_temp_thermal_get_dev(cpu);
	bool lastcpu, was_target;
	int target;

	if (!zonedev)
		return 0;

	target = cpumask_any_but(&zonedev->cpumask, cpu);
	cpumask_clear_cpu(cpu, &zonedev->cpumask);
	lastcpu = target >= nr_cpu_ids;
	/*
	 * Remove the sysfs files, if this is the last cpu in the package
	 * before doing further cleanups.
	 */
	if (lastcpu) {
		struct thermal_zone_device *tzone = zonedev->tzone;

		/*
		 * We must protect against a work function calling
		 * thermal_zone_update, after/while unregister. We null out
		 * the pointer under the zone mutex, so the worker function
		 * won't try to call.
		 */
		mutex_lock(&thermal_zone_mutex);
		zonedev->tzone = NULL;
		mutex_unlock(&thermal_zone_mutex);

		thermal_zone_device_unregister(tzone);
	}

	/* Protect against work and interrupts */
	spin_lock_irq(&pkg_temp_lock);

	/*
	 * Check whether this cpu was the current target and store the new
	 * one. When we drop the lock, then the interrupt notify function
	 * will see the new target.
	 */
	was_target = zonedev->cpu == cpu;
	zonedev->cpu = target;

	/*
	 * If this is the last CPU in the package remove the package
	 * reference from the array and restore the interrupt MSR. When we
	 * drop the lock neither the interrupt notify function nor the
	 * worker will see the package anymore.
	 */
	if (lastcpu) {
		zones[topology_logical_die_id(cpu)] = NULL;
		/* After this point nothing touches the MSR anymore. */
		wrmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT,
		      zonedev->msr_pkg_therm_low, zonedev->msr_pkg_therm_high);
	}

	/*
	 * Check whether there is work scheduled and whether the work is
	 * targeted at the outgoing CPU.
	 */
	if (zonedev->work_scheduled && was_target) {
		/*
		 * To cancel the work we need to drop the lock, otherwise
		 * we might deadlock if the work needs to be flushed.
		 */
		spin_unlock_irq(&pkg_temp_lock);
		cancel_delayed_work_sync(&zonedev->work);
		spin_lock_irq(&pkg_temp_lock);
		/*
		 * If this is not the last cpu in the package and the work
		 * did not run after we dropped the lock above, then we
		 * need to reschedule the work, otherwise the interrupt
		 * stays disabled forever.
		 */
		if (!lastcpu && zonedev->work_scheduled)
			pkg_thermal_schedule_work(target, &zonedev->work);
	}

	spin_unlock_irq(&pkg_temp_lock);

	/* Final cleanup if this is the last cpu */
	if (lastcpu)
		kfree(zonedev);
	return 0;
}