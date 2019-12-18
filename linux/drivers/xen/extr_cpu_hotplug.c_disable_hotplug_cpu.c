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

/* Variables and functions */
 int /*<<< orphan*/  cpu_is_hotpluggable (int) ; 
 scalar_t__ cpu_online (int) ; 
 scalar_t__ cpu_present (int) ; 
 int /*<<< orphan*/  device_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cpu_device (int) ; 
 int /*<<< orphan*/  lock_device_hotplug () ; 
 int /*<<< orphan*/  set_cpu_present (int,int) ; 
 int /*<<< orphan*/  unlock_device_hotplug () ; 
 int /*<<< orphan*/  xen_arch_unregister_cpu (int) ; 

__attribute__((used)) static void disable_hotplug_cpu(int cpu)
{
	if (!cpu_is_hotpluggable(cpu))
		return;
	lock_device_hotplug();
	if (cpu_online(cpu))
		device_offline(get_cpu_device(cpu));
	if (!cpu_online(cpu) && cpu_present(cpu)) {
		xen_arch_unregister_cpu(cpu);
		set_cpu_present(cpu, false);
	}
	unlock_device_hotplug();
}