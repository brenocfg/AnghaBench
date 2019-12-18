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
struct TYPE_2__ {void* value; } ;
union acpi_object {TYPE_1__ integer; void* type; } ;
typedef  void* u32 ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_string ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 void* ACPI_TYPE_INTEGER ; 
 scalar_t__ WMAB_METHOD ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_object_list*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_handle_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static union acpi_object *lg_wmab(u32 method, u32 arg1, u32 arg2)
{
	union acpi_object args[3];
	acpi_status status;
	acpi_handle handle;
	struct acpi_object_list arg;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };

	args[0].type = ACPI_TYPE_INTEGER;
	args[0].integer.value = method;
	args[1].type = ACPI_TYPE_INTEGER;
	args[1].integer.value = arg1;
	args[2].type = ACPI_TYPE_INTEGER;
	args[2].integer.value = arg2;

	status = acpi_get_handle(NULL, (acpi_string) WMAB_METHOD, &handle);
	if (ACPI_FAILURE(status)) {
		pr_err("Cannot get handle");
		return NULL;
	}

	arg.count = 3;
	arg.pointer = args;

	status = acpi_evaluate_object(handle, NULL, &arg, &buffer);
	if (ACPI_FAILURE(status)) {
		acpi_handle_err(handle, "WMAB: call failed.\n");
		return NULL;
	}

	return buffer.pointer;
}