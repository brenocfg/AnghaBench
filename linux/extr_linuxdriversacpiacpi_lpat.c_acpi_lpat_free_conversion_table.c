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
struct acpi_lpat_conversion_table {struct acpi_lpat_conversion_table* lpat; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct acpi_lpat_conversion_table*) ; 

void acpi_lpat_free_conversion_table(struct acpi_lpat_conversion_table
				     *lpat_table)
{
	if (lpat_table) {
		kfree(lpat_table->lpat);
		kfree(lpat_table);
	}
}