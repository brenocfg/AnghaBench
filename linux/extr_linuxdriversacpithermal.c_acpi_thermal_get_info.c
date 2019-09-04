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
struct TYPE_2__ {int cooling_mode; } ;
struct acpi_thermal {scalar_t__ polling_frequency; TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_THERMAL_MODE_ACTIVE ; 
 int EINVAL ; 
 int /*<<< orphan*/  acpi_thermal_aml_dependency_fix (struct acpi_thermal*) ; 
 int /*<<< orphan*/  acpi_thermal_get_polling_frequency (struct acpi_thermal*) ; 
 int acpi_thermal_get_temperature (struct acpi_thermal*) ; 
 int acpi_thermal_get_trip_points (struct acpi_thermal*) ; 
 int acpi_thermal_set_cooling_mode (struct acpi_thermal*,int /*<<< orphan*/ ) ; 
 scalar_t__ tzp ; 

__attribute__((used)) static int acpi_thermal_get_info(struct acpi_thermal *tz)
{
	int result = 0;


	if (!tz)
		return -EINVAL;

	acpi_thermal_aml_dependency_fix(tz);

	/* Get trip points [_CRT, _PSV, etc.] (required) */
	result = acpi_thermal_get_trip_points(tz);
	if (result)
		return result;

	/* Get temperature [_TMP] (required) */
	result = acpi_thermal_get_temperature(tz);
	if (result)
		return result;

	/* Set the cooling mode [_SCP] to active cooling (default) */
	result = acpi_thermal_set_cooling_mode(tz, ACPI_THERMAL_MODE_ACTIVE);
	if (!result)
		tz->flags.cooling_mode = 1;

	/* Get default polling frequency [_TZP] (optional) */
	if (tzp)
		tz->polling_frequency = tzp;
	else
		acpi_thermal_get_polling_frequency(tz);

	return 0;
}