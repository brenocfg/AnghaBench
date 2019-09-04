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
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_processor_update_tsd_coord () ; 

void acpi_processor_throttling_init(void)
{
	if (acpi_processor_update_tsd_coord()) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			"Assume no T-state coordination\n"));
	}

	return;
}