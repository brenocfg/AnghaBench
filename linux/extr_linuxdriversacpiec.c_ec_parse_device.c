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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_ec {scalar_t__ command_addr; scalar_t__ data_addr; unsigned long long gpe; unsigned long long global_lock; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {unsigned long long gpe; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ EC_FLAGS_IGNORE_DSDT_GPE ; 
 int /*<<< orphan*/  METHOD_NAME__CRS ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_walk_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_ec*) ; 
 TYPE_1__* boot_ec ; 
 scalar_t__ boot_ec_is_ecdt ; 
 int /*<<< orphan*/  ec_parse_io_ports ; 

__attribute__((used)) static acpi_status
ec_parse_device(acpi_handle handle, u32 Level, void *context, void **retval)
{
	acpi_status status;
	unsigned long long tmp = 0;
	struct acpi_ec *ec = context;

	/* clear addr values, ec_parse_io_ports depend on it */
	ec->command_addr = ec->data_addr = 0;

	status = acpi_walk_resources(handle, METHOD_NAME__CRS,
				     ec_parse_io_ports, ec);
	if (ACPI_FAILURE(status))
		return status;
	if (ec->data_addr == 0 || ec->command_addr == 0)
		return AE_OK;

	if (boot_ec && boot_ec_is_ecdt && EC_FLAGS_IGNORE_DSDT_GPE) {
		/*
		 * Always inherit the GPE number setting from the ECDT
		 * EC.
		 */
		ec->gpe = boot_ec->gpe;
	} else {
		/* Get GPE bit assignment (EC events). */
		/* TODO: Add support for _GPE returning a package */
		status = acpi_evaluate_integer(handle, "_GPE", NULL, &tmp);
		if (ACPI_FAILURE(status))
			return status;
		ec->gpe = tmp;
	}
	/* Use the global lock for all EC transactions? */
	tmp = 0;
	acpi_evaluate_integer(handle, "_GLK", NULL, &tmp);
	ec->global_lock = tmp;
	ec->handle = handle;
	return AE_CTRL_TERMINATE;
}