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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_device {scalar_t__ handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_VIDEO_BUS_NAME ; 
 int /*<<< orphan*/  AE_ALREADY_EXISTS ; 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 int acpi_bus_get_device (scalar_t__,struct acpi_device**) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_video_bus_match(acpi_handle handle, u32 level, void *context,
			void **return_value)
{
	struct acpi_device *device = context;
	struct acpi_device *sibling;
	int result;

	if (handle == device->handle)
		return AE_CTRL_TERMINATE;

	result = acpi_bus_get_device(handle, &sibling);
	if (result)
		return AE_OK;

	if (!strcmp(acpi_device_name(sibling), ACPI_VIDEO_BUS_NAME))
			return AE_ALREADY_EXISTS;

	return AE_OK;
}