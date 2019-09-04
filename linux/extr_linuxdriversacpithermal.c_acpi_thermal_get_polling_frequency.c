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
struct acpi_thermal {unsigned long long polling_frequency; TYPE_1__* device; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 

__attribute__((used)) static int acpi_thermal_get_polling_frequency(struct acpi_thermal *tz)
{
	acpi_status status = AE_OK;
	unsigned long long tmp;

	if (!tz)
		return -EINVAL;

	status = acpi_evaluate_integer(tz->device->handle, "_TZP", NULL, &tmp);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	tz->polling_frequency = tmp;
	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Polling frequency is %lu dS\n",
			  tz->polling_frequency));

	return 0;
}