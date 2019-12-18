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
struct acpi_table_header {int dummy; } ;
struct acpi_table_dmar {int flags; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_DMAR ; 
 int DMAR_PLATFORM_OPT_IN ; 
 int /*<<< orphan*/  acpi_get_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_table_header**) ; 
 int /*<<< orphan*/  acpi_put_table (struct acpi_table_header*) ; 

bool dmar_platform_optin(void)
{
	struct acpi_table_dmar *dmar;
	acpi_status status;
	bool ret;

	status = acpi_get_table(ACPI_SIG_DMAR, 0,
				(struct acpi_table_header **)&dmar);
	if (ACPI_FAILURE(status))
		return false;

	ret = !!(dmar->flags & DMAR_PLATFORM_OPT_IN);
	acpi_put_table((struct acpi_table_header *)dmar);

	return ret;
}