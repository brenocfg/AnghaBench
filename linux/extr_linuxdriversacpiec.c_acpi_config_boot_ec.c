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
struct acpi_ec {scalar_t__ handle; } ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_ec_free (struct acpi_ec*) ; 
 int acpi_ec_setup (struct acpi_ec*,int) ; 
 int /*<<< orphan*/  acpi_handle_info (scalar_t__,char*,char*,char*) ; 
 struct acpi_ec* boot_ec ; 
 int boot_ec_is_ecdt ; 
 int /*<<< orphan*/  ec_remove_handlers (struct acpi_ec*) ; 

__attribute__((used)) static int acpi_config_boot_ec(struct acpi_ec *ec, acpi_handle handle,
			       bool handle_events, bool is_ecdt)
{
	int ret;

	/*
	 * Changing the ACPI handle results in a re-configuration of the
	 * boot EC. And if it happens after the namespace initialization,
	 * it causes _REG evaluations.
	 */
	if (boot_ec && boot_ec->handle != handle)
		ec_remove_handlers(boot_ec);

	/* Unset old boot EC */
	if (boot_ec != ec)
		acpi_ec_free(boot_ec);

	/*
	 * ECDT device creation is split into acpi_ec_ecdt_probe() and
	 * acpi_ec_ecdt_start(). This function takes care of completing the
	 * ECDT parsing logic as the handle update should be performed
	 * between the installation/uninstallation of the handlers.
	 */
	if (ec->handle != handle)
		ec->handle = handle;

	ret = acpi_ec_setup(ec, handle_events);
	if (ret)
		return ret;

	/* Set new boot EC */
	if (!boot_ec) {
		boot_ec = ec;
		boot_ec_is_ecdt = is_ecdt;
	}

	acpi_handle_info(boot_ec->handle,
			 "Used as boot %s EC to handle transactions%s\n",
			 is_ecdt ? "ECDT" : "DSDT",
			 handle_events ? " and events" : "");
	return ret;
}