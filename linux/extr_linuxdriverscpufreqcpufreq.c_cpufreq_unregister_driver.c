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
struct cpufreq_driver {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 struct cpufreq_driver* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_driver_lock ; 
 int /*<<< orphan*/  cpufreq_interface ; 
 int /*<<< orphan*/  cpuhp_remove_state_nocalls_cpuslocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_read_lock () ; 
 int /*<<< orphan*/  cpus_read_unlock () ; 
 int /*<<< orphan*/  hp_online ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_boost_sysfs_file () ; 
 int /*<<< orphan*/  subsys_interface_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cpufreq_unregister_driver(struct cpufreq_driver *driver)
{
	unsigned long flags;

	if (!cpufreq_driver || (driver != cpufreq_driver))
		return -EINVAL;

	pr_debug("unregistering driver %s\n", driver->name);

	/* Protect against concurrent cpu hotplug */
	cpus_read_lock();
	subsys_interface_unregister(&cpufreq_interface);
	remove_boost_sysfs_file();
	cpuhp_remove_state_nocalls_cpuslocked(hp_online);

	write_lock_irqsave(&cpufreq_driver_lock, flags);

	cpufreq_driver = NULL;

	write_unlock_irqrestore(&cpufreq_driver_lock, flags);
	cpus_read_unlock();

	return 0;
}