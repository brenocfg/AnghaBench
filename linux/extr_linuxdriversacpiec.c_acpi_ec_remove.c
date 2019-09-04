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
struct acpi_ec {int /*<<< orphan*/  command_addr; int /*<<< orphan*/  data_addr; } ;
struct acpi_device {int /*<<< orphan*/ * driver_data; } ;

/* Variables and functions */
 int EINVAL ; 
 struct acpi_ec* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_ec_free (struct acpi_ec*) ; 
 struct acpi_ec* boot_ec ; 
 int /*<<< orphan*/  ec_remove_handlers (struct acpi_ec*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int acpi_ec_remove(struct acpi_device *device)
{
	struct acpi_ec *ec;

	if (!device)
		return -EINVAL;

	ec = acpi_driver_data(device);
	release_region(ec->data_addr, 1);
	release_region(ec->command_addr, 1);
	device->driver_data = NULL;
	if (ec != boot_ec) {
		ec_remove_handlers(ec);
		acpi_ec_free(ec);
	}
	return 0;
}