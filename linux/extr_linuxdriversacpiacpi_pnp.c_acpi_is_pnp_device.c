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
struct acpi_device {int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_pnp_handler ; 
 scalar_t__ is_cmos_rtc_device (struct acpi_device*) ; 

bool acpi_is_pnp_device(struct acpi_device *adev)
{
	return adev->handler == &acpi_pnp_handler || is_cmos_rtc_device(adev);
}