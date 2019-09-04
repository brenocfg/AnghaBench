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

__attribute__((used)) static int physflat_acpi_madt_oem_check(char *oem_id, char *oem_table_id)
{
#ifdef CONFIG_ACPI
	/*
	 * Quirk: some x86_64 machines can only use physical APIC mode
	 * regardless of how many processors are present (x86_64 ES7000
	 * is an example).
	 */
	if (acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID &&
		(acpi_gbl_FADT.flags & ACPI_FADT_APIC_PHYSICAL)) {
		printk(KERN_DEBUG "system APIC only can use physical flat");
		return 1;
	}

	if (!strncmp(oem_id, "IBM", 3) && !strncmp(oem_table_id, "EXA", 3)) {
		printk(KERN_DEBUG "IBM Summit detected, will use apic physical");
		return 1;
	}
#endif

	return 0;
}