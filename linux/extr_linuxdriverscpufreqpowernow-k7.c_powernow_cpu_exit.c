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
struct cpufreq_policy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powernow_table ; 

__attribute__((used)) static int powernow_cpu_exit(struct cpufreq_policy *policy)
{
#ifdef CONFIG_X86_POWERNOW_K7_ACPI
	if (acpi_processor_perf) {
		acpi_processor_unregister_performance(0);
		free_cpumask_var(acpi_processor_perf->shared_cpu_map);
		kfree(acpi_processor_perf);
	}
#endif

	kfree(powernow_table);
	return 0;
}