#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct acpi_table_header {int dummy; } ;
struct acpi_table_desc {size_t length; int /*<<< orphan*/  pointer; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/ * tables; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 TYPE_1__ acpi_gbl_root_table_list ; 
 int /*<<< orphan*/  acpi_tb_acquire_table (int /*<<< orphan*/ *,struct acpi_table_header**,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_tb_release_table (struct acpi_table_header*,size_t,scalar_t__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,struct acpi_table_header*,size_t) ; 

__attribute__((used)) static u8
acpi_tb_compare_tables(struct acpi_table_desc *table_desc, u32 table_index)
{
	acpi_status status = AE_OK;
	u8 is_identical;
	struct acpi_table_header *table;
	u32 table_length;
	u8 table_flags;

	status =
	    acpi_tb_acquire_table(&acpi_gbl_root_table_list.tables[table_index],
				  &table, &table_length, &table_flags);
	if (ACPI_FAILURE(status)) {
		return (FALSE);
	}

	/*
	 * Check for a table match on the entire table length,
	 * not just the header.
	 */
	is_identical = (u8)((table_desc->length != table_length ||
			     memcmp(table_desc->pointer, table, table_length)) ?
			    FALSE : TRUE);

	/* Release the acquired table */

	acpi_tb_release_table(table, table_length, table_flags);
	return (is_identical);
}