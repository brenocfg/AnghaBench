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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */

int acpi_ioapic_registered(acpi_handle handle, u32 gsi_base)
{
	int ret = 0;

#ifdef CONFIG_ACPI_HOTPLUG_IOAPIC
	mutex_lock(&acpi_ioapic_lock);
	ret  = mp_ioapic_registered(gsi_base);
	mutex_unlock(&acpi_ioapic_lock);
#endif

	return ret;
}