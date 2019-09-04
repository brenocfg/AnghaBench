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
struct acpi_ec {int /*<<< orphan*/  handle; int /*<<< orphan*/  command_addr; int /*<<< orphan*/  data_addr; } ;
struct acpi_device {struct acpi_ec* driver_data; int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ECDT_HID ; 
 int /*<<< orphan*/  ACPI_EC_CLASS ; 
 int /*<<< orphan*/  ACPI_EC_DEVICE_NAME ; 
 scalar_t__ AE_CTRL_TERMINATE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int acpi_config_boot_ec (struct acpi_ec*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_hid (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 struct acpi_ec* acpi_ec_alloc () ; 
 int /*<<< orphan*/  acpi_ec_free (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_remove_query_handlers (struct acpi_ec*,int,int /*<<< orphan*/ ) ; 
 int acpi_ec_setup (struct acpi_ec*,int) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ acpi_is_boot_ec (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_walk_dep_device_list (int /*<<< orphan*/ ) ; 
 struct acpi_ec* boot_ec ; 
 int boot_ec_is_ecdt ; 
 scalar_t__ ec_parse_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_ec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_region (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_ec_add(struct acpi_device *device)
{
	struct acpi_ec *ec = NULL;
	int ret;
	bool is_ecdt = false;
	acpi_status status;

	strcpy(acpi_device_name(device), ACPI_EC_DEVICE_NAME);
	strcpy(acpi_device_class(device), ACPI_EC_CLASS);

	if (!strcmp(acpi_device_hid(device), ACPI_ECDT_HID)) {
		is_ecdt = true;
		ec = boot_ec;
	} else {
		ec = acpi_ec_alloc();
		if (!ec)
			return -ENOMEM;
		status = ec_parse_device(device->handle, 0, ec, NULL);
		if (status != AE_CTRL_TERMINATE) {
			ret = -EINVAL;
			goto err_alloc;
		}
	}

	if (acpi_is_boot_ec(ec)) {
		boot_ec_is_ecdt = is_ecdt;
		if (!is_ecdt) {
			/*
			 * Trust PNP0C09 namespace location rather than
			 * ECDT ID. But trust ECDT GPE rather than _GPE
			 * because of ASUS quirks, so do not change
			 * boot_ec->gpe to ec->gpe.
			 */
			boot_ec->handle = ec->handle;
			acpi_handle_debug(ec->handle, "duplicated.\n");
			acpi_ec_free(ec);
			ec = boot_ec;
		}
		ret = acpi_config_boot_ec(ec, ec->handle, true, is_ecdt);
	} else
		ret = acpi_ec_setup(ec, true);
	if (ret)
		goto err_query;

	device->driver_data = ec;

	ret = !!request_region(ec->data_addr, 1, "EC data");
	WARN(!ret, "Could not request EC data io port 0x%lx", ec->data_addr);
	ret = !!request_region(ec->command_addr, 1, "EC cmd");
	WARN(!ret, "Could not request EC cmd io port 0x%lx", ec->command_addr);

	if (!is_ecdt) {
		/* Reprobe devices depending on the EC */
		acpi_walk_dep_device_list(ec->handle);
	}
	acpi_handle_debug(ec->handle, "enumerated.\n");
	return 0;

err_query:
	if (ec != boot_ec)
		acpi_ec_remove_query_handlers(ec, true, 0);
err_alloc:
	if (ec != boot_ec)
		acpi_ec_free(ec);
	return ret;
}