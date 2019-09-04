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
struct dock_station {int /*<<< orphan*/  handle; } ;
struct device_attribute {int dummy; } ;
struct device {struct dock_station* platform_data; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int acpi_device_enumerated (struct acpi_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t show_docked(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	struct dock_station *dock_station = dev->platform_data;
	struct acpi_device *adev = NULL;

	acpi_bus_get_device(dock_station->handle, &adev);
	return snprintf(buf, PAGE_SIZE, "%u\n", acpi_device_enumerated(adev));
}