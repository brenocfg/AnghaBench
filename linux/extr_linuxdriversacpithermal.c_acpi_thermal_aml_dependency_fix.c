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
struct acpi_thermal {TYPE_1__* device; } ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int ACPI_THERMAL_MAX_ACTIVE ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 

__attribute__((used)) static void acpi_thermal_aml_dependency_fix(struct acpi_thermal *tz)
{
	acpi_handle handle = tz->device->handle;
	unsigned long long value;
	int i;

	acpi_evaluate_integer(handle, "_CRT", NULL, &value);
	acpi_evaluate_integer(handle, "_HOT", NULL, &value);
	acpi_evaluate_integer(handle, "_PSV", NULL, &value);
	for (i = 0; i < ACPI_THERMAL_MAX_ACTIVE; i++) {
		char name[5] = { '_', 'A', 'C', ('0' + i), '\0' };
		acpi_status status;

		status = acpi_evaluate_integer(handle, name, NULL, &value);
		if (status == AE_NOT_FOUND)
			break;
	}
	acpi_evaluate_integer(handle, "_TMP", NULL, &value);
}