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
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
struct acpi_power_resource {int /*<<< orphan*/  name; TYPE_1__ device; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __acpi_power_off(struct acpi_power_resource *resource)
{
	acpi_status status;

	status = acpi_evaluate_object(resource->device.handle, "_OFF",
				      NULL, NULL);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Power resource [%s] turned off\n",
			  resource->name));
	return 0;
}