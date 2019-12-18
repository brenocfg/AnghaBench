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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_device_power_manageable (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_update_power (struct acpi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_pci_refresh_power_state(struct pci_dev *dev)
{
	struct acpi_device *adev = ACPI_COMPANION(&dev->dev);

	if (adev && acpi_device_power_manageable(adev))
		acpi_device_update_power(adev, NULL);
}