#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct acpi_table_header {int dummy; } ;
struct acpi_table_desc {int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;
struct TYPE_4__ {scalar_t__ Xfacs; scalar_t__ facs; scalar_t__ Xdsdt; } ;
struct TYPE_3__ {struct acpi_table_desc* tables; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  acpi_gbl_dsdt_index ; 
 int /*<<< orphan*/  acpi_gbl_facs_index ; 
 size_t acpi_gbl_fadt_index ; 
 int /*<<< orphan*/  acpi_gbl_reduced_hardware ; 
 TYPE_1__ acpi_gbl_root_table_list ; 
 int /*<<< orphan*/  acpi_gbl_xfacs_index ; 
 int /*<<< orphan*/  acpi_tb_create_local_fadt (struct acpi_table_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tb_get_table (struct acpi_table_desc*,struct acpi_table_header**) ; 
 int /*<<< orphan*/  acpi_tb_install_standard_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_tb_put_table (struct acpi_table_desc*) ; 
 int /*<<< orphan*/  acpi_tb_verify_checksum (struct acpi_table_header*,int /*<<< orphan*/ ) ; 

void acpi_tb_parse_fadt(void)
{
	u32 length;
	struct acpi_table_header *table;
	struct acpi_table_desc *fadt_desc;
	acpi_status status;

	/*
	 * The FADT has multiple versions with different lengths,
	 * and it contains pointers to both the DSDT and FACS tables.
	 *
	 * Get a local copy of the FADT and convert it to a common format
	 * Map entire FADT, assumed to be smaller than one page.
	 */
	fadt_desc = &acpi_gbl_root_table_list.tables[acpi_gbl_fadt_index];
	status = acpi_tb_get_table(fadt_desc, &table);
	if (ACPI_FAILURE(status)) {
		return;
	}
	length = fadt_desc->length;

	/*
	 * Validate the FADT checksum before we copy the table. Ignore
	 * checksum error as we want to try to get the DSDT and FACS.
	 */
	(void)acpi_tb_verify_checksum(table, length);

	/* Create a local copy of the FADT in common ACPI 2.0+ format */

	acpi_tb_create_local_fadt(table, length);

	/* All done with the real FADT, unmap it */

	acpi_tb_put_table(fadt_desc);

	/* Obtain the DSDT and FACS tables via their addresses within the FADT */

	acpi_tb_install_standard_table((acpi_physical_address)acpi_gbl_FADT.
				       Xdsdt,
				       ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL,
				       FALSE, TRUE, &acpi_gbl_dsdt_index);

	/* If Hardware Reduced flag is set, there is no FACS */

	if (!acpi_gbl_reduced_hardware) {
		if (acpi_gbl_FADT.facs) {
			acpi_tb_install_standard_table((acpi_physical_address)
						       acpi_gbl_FADT.facs,
						       ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL,
						       FALSE, TRUE,
						       &acpi_gbl_facs_index);
		}
		if (acpi_gbl_FADT.Xfacs) {
			acpi_tb_install_standard_table((acpi_physical_address)
						       acpi_gbl_FADT.Xfacs,
						       ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL,
						       FALSE, TRUE,
						       &acpi_gbl_xfacs_index);
		}
	}
}