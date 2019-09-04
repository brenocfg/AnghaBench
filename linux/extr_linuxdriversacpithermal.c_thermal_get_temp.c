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
struct thermal_zone_device {struct acpi_thermal* devdata; } ;
struct acpi_thermal {int /*<<< orphan*/  kelvin_offset; int /*<<< orphan*/  temperature; } ;

/* Variables and functions */
 int DECI_KELVIN_TO_MILLICELSIUS_WITH_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int acpi_thermal_get_temperature (struct acpi_thermal*) ; 

__attribute__((used)) static int thermal_get_temp(struct thermal_zone_device *thermal, int *temp)
{
	struct acpi_thermal *tz = thermal->devdata;
	int result;

	if (!tz)
		return -EINVAL;

	result = acpi_thermal_get_temperature(tz);
	if (result)
		return result;

	*temp = DECI_KELVIN_TO_MILLICELSIUS_WITH_OFFSET(tz->temperature,
							tz->kelvin_offset);
	return 0;
}