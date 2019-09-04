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
struct acpi_processor {int /*<<< orphan*/  handle; int /*<<< orphan*/  performance; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_has_method (int /*<<< orphan*/ ,char*) ; 
 int acpi_processor_get_performance_control (struct acpi_processor*) ; 
 int acpi_processor_get_performance_states (struct acpi_processor*) ; 
 int acpi_processor_get_platform_limit (struct acpi_processor*) ; 
 int ignore_ppc ; 

int acpi_processor_get_performance_info(struct acpi_processor *pr)
{
	int result = 0;

	if (!pr || !pr->performance || !pr->handle)
		return -EINVAL;

	if (!acpi_has_method(pr->handle, "_PCT")) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "ACPI-based processor performance control unavailable\n"));
		return -ENODEV;
	}

	result = acpi_processor_get_performance_control(pr);
	if (result)
		goto update_bios;

	result = acpi_processor_get_performance_states(pr);
	if (result)
		goto update_bios;

	/* We need to call _PPC once when cpufreq starts */
	if (ignore_ppc != 1)
		result = acpi_processor_get_platform_limit(pr);

	return result;

	/*
	 * Having _PPC but missing frequencies (_PSS, _PCT) is a very good hint that
	 * the BIOS is older than the CPU and does not know its frequencies
	 */
 update_bios:
#ifdef CONFIG_X86
	if (acpi_has_method(pr->handle, "_PPC")) {
		if(boot_cpu_has(X86_FEATURE_EST))
			printk(KERN_WARNING FW_BUG "BIOS needs update for CPU "
			       "frequency support\n");
	}
#endif
	return result;
}