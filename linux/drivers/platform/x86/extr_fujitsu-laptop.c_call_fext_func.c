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
struct TYPE_2__ {int value; int /*<<< orphan*/  type; } ;
union acpi_object {TYPE_1__ integer; } ;
struct acpi_object_list {int member_0; union acpi_object* member_1; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,struct acpi_object_list*,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  acpi_handle_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int call_fext_func(struct acpi_device *device,
			  int func, int op, int feature, int state)
{
	union acpi_object params[4] = {
		{ .integer.type = ACPI_TYPE_INTEGER, .integer.value = func },
		{ .integer.type = ACPI_TYPE_INTEGER, .integer.value = op },
		{ .integer.type = ACPI_TYPE_INTEGER, .integer.value = feature },
		{ .integer.type = ACPI_TYPE_INTEGER, .integer.value = state }
	};
	struct acpi_object_list arg_list = { 4, params };
	unsigned long long value;
	acpi_status status;

	status = acpi_evaluate_integer(device->handle, "FUNC", &arg_list,
				       &value);
	if (ACPI_FAILURE(status)) {
		acpi_handle_err(device->handle, "Failed to evaluate FUNC\n");
		return -ENODEV;
	}

	acpi_handle_debug(device->handle,
			  "FUNC 0x%x (args 0x%x, 0x%x, 0x%x) returned 0x%x\n",
			  func, op, feature, state, (int)value);
	return value;
}