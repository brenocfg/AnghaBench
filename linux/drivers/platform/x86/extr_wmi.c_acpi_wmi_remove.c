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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_SPACE_EC ; 
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_remove_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_wmi_ec_space_handler ; 
 int /*<<< orphan*/  acpi_wmi_notify_handler ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmi_bus_class ; 
 int /*<<< orphan*/  wmi_free_devices (struct acpi_device*) ; 

__attribute__((used)) static int acpi_wmi_remove(struct platform_device *device)
{
	struct acpi_device *acpi_device = ACPI_COMPANION(&device->dev);

	acpi_remove_notify_handler(acpi_device->handle, ACPI_DEVICE_NOTIFY,
				   acpi_wmi_notify_handler);
	acpi_remove_address_space_handler(acpi_device->handle,
				ACPI_ADR_SPACE_EC, &acpi_wmi_ec_space_handler);
	wmi_free_devices(acpi_device);
	device_destroy(&wmi_bus_class, MKDEV(0, 0));

	return 0;
}