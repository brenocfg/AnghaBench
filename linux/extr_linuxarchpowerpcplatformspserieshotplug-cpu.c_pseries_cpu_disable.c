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
struct TYPE_2__ {int /*<<< orphan*/  processorCount; } ;

/* Variables and functions */
 int boot_cpuid ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpu_online (int,int) ; 
 int smp_processor_id () ; 
 TYPE_1__* vdso_data ; 
 int /*<<< orphan*/  xics_migrate_irqs_away () ; 
 scalar_t__ xive_enabled () ; 
 int /*<<< orphan*/  xive_smp_disable_cpu () ; 

__attribute__((used)) static int pseries_cpu_disable(void)
{
	int cpu = smp_processor_id();

	set_cpu_online(cpu, false);
	vdso_data->processorCount--;

	/*fix boot_cpuid here*/
	if (cpu == boot_cpuid)
		boot_cpuid = cpumask_any(cpu_online_mask);

	/* FIXME: abstract this to not be platform specific later on */
	if (xive_enabled())
		xive_smp_disable_cpu();
	else
		xics_migrate_irqs_away();
	return 0;
}