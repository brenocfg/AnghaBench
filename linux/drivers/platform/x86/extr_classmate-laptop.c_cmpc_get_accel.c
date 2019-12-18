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
struct TYPE_4__ {unsigned char* pointer; } ;
struct TYPE_3__ {int value; } ;
union acpi_object {TYPE_2__ buffer; void* type; TYPE_1__ integer; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 void* ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

__attribute__((used)) static acpi_status cmpc_get_accel(acpi_handle handle,
				  unsigned char *x,
				  unsigned char *y,
				  unsigned char *z)
{
	union acpi_object param[2];
	struct acpi_object_list input;
	struct acpi_buffer output = { ACPI_ALLOCATE_BUFFER, NULL };
	unsigned char *locs;
	acpi_status status;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].integer.value = 0x01;
	param[1].type = ACPI_TYPE_INTEGER;
	input.count = 2;
	input.pointer = param;
	status = acpi_evaluate_object(handle, "ACMD", &input, &output);
	if (ACPI_SUCCESS(status)) {
		union acpi_object *obj;
		obj = output.pointer;
		locs = obj->buffer.pointer;
		*x = locs[0];
		*y = locs[1];
		*z = locs[2];
		kfree(output.pointer);
	}
	return status;
}