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
typedef  int /*<<< orphan*/  u64 ;
struct acpi_device {int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/ * acpi_handle ;

/* Variables and functions */
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ *,struct acpi_device**) ; 
 struct acpi_device* acpi_find_child_device (struct acpi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static acpi_handle acpi_get_child(acpi_handle handle, u64 addr)
{
	struct acpi_device *adev;

	if (!handle || acpi_bus_get_device(handle, &adev))
		return NULL;

	adev = acpi_find_child_device(adev, addr, false);
	return adev ? adev->handle : NULL;
}