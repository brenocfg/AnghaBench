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
struct acpi_table_desc {int flags; scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_PHYSADDR_TO_PTR (scalar_t__) ; 
 scalar_t__ ACPI_PTR_TO_PHYSADDR (int /*<<< orphan*/ *) ; 
 int ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL ; 
 int ACPI_TABLE_ORIGIN_MASK ; 
 int /*<<< orphan*/  acpi_tb_invalidate_table (struct acpi_table_desc*) ; 
 int /*<<< orphan*/  return_VOID ; 
 int /*<<< orphan*/  tb_uninstall_table ; 

void acpi_tb_uninstall_table(struct acpi_table_desc *table_desc)
{

	ACPI_FUNCTION_TRACE(tb_uninstall_table);

	/* Table must be installed */

	if (!table_desc->address) {
		return_VOID;
	}

	acpi_tb_invalidate_table(table_desc);

	if ((table_desc->flags & ACPI_TABLE_ORIGIN_MASK) ==
	    ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL) {
		ACPI_FREE(ACPI_PHYSADDR_TO_PTR(table_desc->address));
	}

	table_desc->address = ACPI_PTR_TO_PHYSADDR(NULL);
	return_VOID;
}