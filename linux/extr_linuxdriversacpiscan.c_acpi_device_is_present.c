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
struct TYPE_2__ {scalar_t__ functional; scalar_t__ present; } ;
struct acpi_device {TYPE_1__ status; } ;

/* Variables and functions */

bool acpi_device_is_present(const struct acpi_device *adev)
{
	return adev->status.present || adev->status.functional;
}