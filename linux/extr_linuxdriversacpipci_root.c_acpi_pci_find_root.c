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
struct acpi_pci_root {int dummy; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 struct acpi_pci_root* acpi_driver_data (struct acpi_device*) ; 
 scalar_t__ acpi_match_device_ids (struct acpi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  root_device_ids ; 

struct acpi_pci_root *acpi_pci_find_root(acpi_handle handle)
{
	struct acpi_pci_root *root;
	struct acpi_device *device;

	if (acpi_bus_get_device(handle, &device) ||
	    acpi_match_device_ids(device, root_device_ids))
		return NULL;

	root = acpi_driver_data(device);

	return root;
}