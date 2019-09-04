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
struct TYPE_4__ {scalar_t__ length; scalar_t__ checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BIOS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 TYPE_1__* acpi_gbl_DSDT ; 
 TYPE_1__ acpi_gbl_original_dsdt_header ; 
 int /*<<< orphan*/  acpi_tb_print_table_header (int /*<<< orphan*/ ,TYPE_1__*) ; 

void acpi_tb_check_dsdt_header(void)
{

	/* Compare original length and checksum to current values */

	if (acpi_gbl_original_dsdt_header.length != acpi_gbl_DSDT->length ||
	    acpi_gbl_original_dsdt_header.checksum != acpi_gbl_DSDT->checksum) {
		ACPI_BIOS_ERROR((AE_INFO,
				 "The DSDT has been corrupted or replaced - "
				 "old, new headers below"));

		acpi_tb_print_table_header(0, &acpi_gbl_original_dsdt_header);
		acpi_tb_print_table_header(0, acpi_gbl_DSDT);

		ACPI_ERROR((AE_INFO,
			    "Please send DMI info to linux-acpi@vger.kernel.org\n"
			    "If system does not work as expected, please boot with acpi=copy_dsdt"));

		/* Disable further error messages */

		acpi_gbl_original_dsdt_header.length = acpi_gbl_DSDT->length;
		acpi_gbl_original_dsdt_header.checksum =
		    acpi_gbl_DSDT->checksum;
	}
}