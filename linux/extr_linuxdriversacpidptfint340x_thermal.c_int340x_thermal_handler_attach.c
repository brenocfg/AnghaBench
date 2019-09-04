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
struct acpi_device_id {scalar_t__ driver_data; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_INT340X_THERMAL ; 
 int /*<<< orphan*/  CONFIG_INTEL_SOC_DTS_THERMAL ; 
 scalar_t__ INT3401_DEVICE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_create_platform_device (struct acpi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int int340x_thermal_handler_attach(struct acpi_device *adev,
					const struct acpi_device_id *id)
{
	if (IS_ENABLED(CONFIG_INT340X_THERMAL))
		acpi_create_platform_device(adev, NULL);
	/* Intel SoC DTS thermal driver needs INT3401 to set IRQ descriptor */
	else if (IS_ENABLED(CONFIG_INTEL_SOC_DTS_THERMAL) &&
		 id->driver_data == INT3401_DEVICE)
		acpi_create_platform_device(adev, NULL);
	return 1;
}