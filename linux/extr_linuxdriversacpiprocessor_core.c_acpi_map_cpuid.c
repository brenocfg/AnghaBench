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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ phys_cpuid_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ invalid_phys_cpuid (scalar_t__) ; 
 int nr_cpu_ids ; 

int acpi_map_cpuid(phys_cpuid_t phys_id, u32 acpi_id)
{
#ifdef CONFIG_SMP
	int i;
#endif

	if (invalid_phys_cpuid(phys_id)) {
		/*
		 * On UP processor, there is no _MAT or MADT table.
		 * So above phys_id is always set to PHYS_CPUID_INVALID.
		 *
		 * BIOS may define multiple CPU handles even for UP processor.
		 * For example,
		 *
		 * Scope (_PR)
		 * {
		 *     Processor (CPU0, 0x00, 0x00000410, 0x06) {}
		 *     Processor (CPU1, 0x01, 0x00000410, 0x06) {}
		 *     Processor (CPU2, 0x02, 0x00000410, 0x06) {}
		 *     Processor (CPU3, 0x03, 0x00000410, 0x06) {}
		 * }
		 *
		 * Ignores phys_id and always returns 0 for the processor
		 * handle with acpi id 0 if nr_cpu_ids is 1.
		 * This should be the case if SMP tables are not found.
		 * Return -EINVAL for other CPU's handle.
		 */
		if (nr_cpu_ids <= 1 && acpi_id == 0)
			return acpi_id;
		else
			return -EINVAL;
	}

#ifdef CONFIG_SMP
	for_each_possible_cpu(i) {
		if (cpu_physical_id(i) == phys_id)
			return i;
	}
#else
	/* In UP kernel, only processor 0 is valid */
	if (phys_id == 0)
		return phys_id;
#endif
	return -ENODEV;
}