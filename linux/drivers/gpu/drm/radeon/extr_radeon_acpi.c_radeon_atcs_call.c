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
struct TYPE_4__ {int value; } ;
struct TYPE_3__ {union acpi_object* pointer; int /*<<< orphan*/  length; } ;
union acpi_object {TYPE_2__ integer; void* type; TYPE_1__ buffer; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/  length; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 void* ACPI_TYPE_BUFFER ; 
 void* ACPI_TYPE_INTEGER ; 
 scalar_t__ AE_NOT_FOUND ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_format_exception (scalar_t__) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

__attribute__((used)) static union acpi_object *radeon_atcs_call(acpi_handle handle, int function,
					   struct acpi_buffer *params)
{
	acpi_status status;
	union acpi_object atcs_arg_elements[2];
	struct acpi_object_list atcs_arg;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };

	atcs_arg.count = 2;
	atcs_arg.pointer = &atcs_arg_elements[0];

	atcs_arg_elements[0].type = ACPI_TYPE_INTEGER;
	atcs_arg_elements[0].integer.value = function;

	if (params) {
		atcs_arg_elements[1].type = ACPI_TYPE_BUFFER;
		atcs_arg_elements[1].buffer.length = params->length;
		atcs_arg_elements[1].buffer.pointer = params->pointer;
	} else {
		/* We need a second fake parameter */
		atcs_arg_elements[1].type = ACPI_TYPE_INTEGER;
		atcs_arg_elements[1].integer.value = 0;
	}

	status = acpi_evaluate_object(handle, "ATCS", &atcs_arg, &buffer);

	/* Fail only if calling the method fails and ATIF is supported */
	if (ACPI_FAILURE(status) && status != AE_NOT_FOUND) {
		DRM_DEBUG_DRIVER("failed to evaluate ATCS got %s\n",
				 acpi_format_exception(status));
		kfree(buffer.pointer);
		return NULL;
	}

	return buffer.pointer;
}