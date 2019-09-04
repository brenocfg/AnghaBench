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

__attribute__((used)) static bool x2apic_fadt_phys(void)
{
#ifdef CONFIG_ACPI
	if ((acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID) &&
		(acpi_gbl_FADT.flags & ACPI_FADT_APIC_PHYSICAL)) {
		printk(KERN_DEBUG "System requires x2apic physical mode\n");
		return true;
	}
#endif
	return false;
}