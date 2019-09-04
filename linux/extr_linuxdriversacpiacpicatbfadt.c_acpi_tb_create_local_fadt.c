#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct acpi_table_header {int /*<<< orphan*/  revision; } ;
struct acpi_table_fadt {int dummy; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BIOS_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FADT_CONFORMANCE ; 
 int ACPI_FADT_HW_REDUCED ; 
 int /*<<< orphan*/  ACPI_MIN (int,int) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  acpi_gbl_reduced_hardware ; 
 int /*<<< orphan*/  acpi_tb_convert_fadt () ; 
 int /*<<< orphan*/  acpi_tb_setup_fadt_registers () ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct acpi_table_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void acpi_tb_create_local_fadt(struct acpi_table_header *table, u32 length)
{
	/*
	 * Check if the FADT is larger than the largest table that we expect
	 * (typically the current ACPI specification version). If so, truncate
	 * the table, and issue a warning.
	 */
	if (length > sizeof(struct acpi_table_fadt)) {
		ACPI_BIOS_WARNING((AE_INFO,
				   "FADT (revision %u) is longer than %s length, "
				   "truncating length %u to %u",
				   table->revision, ACPI_FADT_CONFORMANCE,
				   length,
				   (u32)sizeof(struct acpi_table_fadt)));
	}

	/* Clear the entire local FADT */

	memset(&acpi_gbl_FADT, 0, sizeof(struct acpi_table_fadt));

	/* Copy the original FADT, up to sizeof (struct acpi_table_fadt) */

	memcpy(&acpi_gbl_FADT, table,
	       ACPI_MIN(length, sizeof(struct acpi_table_fadt)));

	/* Take a copy of the Hardware Reduced flag */

	acpi_gbl_reduced_hardware = FALSE;
	if (acpi_gbl_FADT.flags & ACPI_FADT_HW_REDUCED) {
		acpi_gbl_reduced_hardware = TRUE;
	}

	/* Convert the local copy of the FADT to the common internal format */

	acpi_tb_convert_fadt();

	/* Initialize the global ACPI register structures */

	acpi_tb_setup_fadt_registers();
}