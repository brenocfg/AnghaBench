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
 unsigned int ACPI_STA_DEVICE_ENABLED ; 
 unsigned int ACPI_STA_DEVICE_FUNCTIONING ; 

__attribute__((used)) static inline bool device_status_valid(unsigned int sta)
{
	/*
	 * ACPI spec says that _STA may return bit 0 clear with bit 3 set
	 * if the device is valid but does not require a device driver to be
	 * loaded (Section 6.3.7 of ACPI 5.0A).
	 */
	unsigned int mask = ACPI_STA_DEVICE_ENABLED | ACPI_STA_DEVICE_FUNCTIONING;
	return (sta & mask) == mask;
}