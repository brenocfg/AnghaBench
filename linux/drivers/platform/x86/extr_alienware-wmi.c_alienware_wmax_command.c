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
struct TYPE_2__ {scalar_t__ value; } ;
union acpi_object {scalar_t__ type; TYPE_1__ integer; } ;
typedef  int u32 ;
struct wmax_basic_args {int dummy; } ;
struct acpi_buffer {struct wmax_basic_args* pointer; scalar_t__ length; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 scalar_t__ ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  WMAX_CONTROL_GUID ; 
 int /*<<< orphan*/  kfree (struct wmax_basic_args*) ; 
 int /*<<< orphan*/  wmi_evaluate_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct acpi_buffer*,struct acpi_buffer*) ; 

__attribute__((used)) static acpi_status alienware_wmax_command(struct wmax_basic_args *in_args,
					  u32 command, int *out_data)
{
	acpi_status status;
	union acpi_object *obj;
	struct acpi_buffer input;
	struct acpi_buffer output;

	input.length = (acpi_size) sizeof(*in_args);
	input.pointer = in_args;
	if (out_data) {
		output.length = ACPI_ALLOCATE_BUFFER;
		output.pointer = NULL;
		status = wmi_evaluate_method(WMAX_CONTROL_GUID, 0,
					     command, &input, &output);
		if (ACPI_SUCCESS(status)) {
			obj = (union acpi_object *)output.pointer;
			if (obj && obj->type == ACPI_TYPE_INTEGER)
				*out_data = (u32)obj->integer.value;
		}
		kfree(output.pointer);
	} else {
		status = wmi_evaluate_method(WMAX_CONTROL_GUID, 0,
					     command, &input, NULL);
	}
	return status;
}