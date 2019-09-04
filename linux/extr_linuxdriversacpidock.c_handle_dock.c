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
struct TYPE_2__ {int value; } ;
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  type; } ;
struct dock_station {int /*<<< orphan*/  handle; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ acpi_evaluate_integer (int /*<<< orphan*/ ,char*,struct acpi_object_list*,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_handle_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  acpi_handle_info (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void handle_dock(struct dock_station *ds, int dock)
{
	acpi_status status;
	struct acpi_object_list arg_list;
	union acpi_object arg;
	unsigned long long value;

	acpi_handle_info(ds->handle, "%s\n", dock ? "docking" : "undocking");

	/* _DCK method has one argument */
	arg_list.count = 1;
	arg_list.pointer = &arg;
	arg.type = ACPI_TYPE_INTEGER;
	arg.integer.value = dock;
	status = acpi_evaluate_integer(ds->handle, "_DCK", &arg_list, &value);
	if (ACPI_FAILURE(status) && status != AE_NOT_FOUND)
		acpi_handle_err(ds->handle, "Failed to execute _DCK (0x%x)\n",
				status);
}