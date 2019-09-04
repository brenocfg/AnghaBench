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
struct acpi_smbus_cmi {int /*<<< orphan*/  adapter; } ;
struct acpi_device {int /*<<< orphan*/ * driver_data; } ;

/* Variables and functions */
 struct acpi_smbus_cmi* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct acpi_smbus_cmi*) ; 

__attribute__((used)) static int acpi_smbus_cmi_remove(struct acpi_device *device)
{
	struct acpi_smbus_cmi *smbus_cmi = acpi_driver_data(device);

	i2c_del_adapter(&smbus_cmi->adapter);
	kfree(smbus_cmi);
	device->driver_data = NULL;

	return 0;
}