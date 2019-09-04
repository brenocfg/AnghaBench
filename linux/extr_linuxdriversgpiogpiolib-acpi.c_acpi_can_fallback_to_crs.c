#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ properties; } ;
struct acpi_device {scalar_t__ driver_gpios; TYPE_1__ data; } ;

/* Variables and functions */

bool acpi_can_fallback_to_crs(struct acpi_device *adev, const char *con_id)
{
	/* Never allow fallback if the device has properties */
	if (adev->data.properties || adev->driver_gpios)
		return false;

	return con_id == NULL;
}