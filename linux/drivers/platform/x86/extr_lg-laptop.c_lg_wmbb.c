#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; int /*<<< orphan*/ * pointer; } ;
struct TYPE_3__ {int value; } ;
union acpi_object {TYPE_2__ buffer; void* type; TYPE_1__ integer; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_string ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 void* ACPI_TYPE_BUFFER ; 
 void* ACPI_TYPE_INTEGER ; 
 scalar_t__ WMBB_METHOD ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_object_list*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_handle_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static union acpi_object *lg_wmbb(u32 method_id, u32 arg1, u32 arg2)
{
	union acpi_object args[3];
	acpi_status status;
	acpi_handle handle;
	struct acpi_object_list arg;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	u8 buf[32];

	*(u32 *)buf = method_id;
	*(u32 *)(buf + 4) = arg1;
	*(u32 *)(buf + 16) = arg2;
	args[0].type = ACPI_TYPE_INTEGER;
	args[0].integer.value = 0; /* ignored */
	args[1].type = ACPI_TYPE_INTEGER;
	args[1].integer.value = 1; /* Must be 1 or 2. Does not matter which */
	args[2].type = ACPI_TYPE_BUFFER;
	args[2].buffer.length = 32;
	args[2].buffer.pointer = buf;

	status = acpi_get_handle(NULL, (acpi_string)WMBB_METHOD, &handle);
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

	return (union acpi_object *)buffer.pointer;
}