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
struct acpi_object_list {int count; union acpi_object* pointer; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,struct acpi_object_list*,unsigned long long*) ; 

__attribute__((used)) static acpi_status cmpc_get_tablet(acpi_handle handle,
				   unsigned long long *value)
{
	union acpi_object param;
	struct acpi_object_list input;
	unsigned long long output;
	acpi_status status;

	param.type = ACPI_TYPE_INTEGER;
	param.integer.value = 0x01;
	input.count = 1;
	input.pointer = &param;
	status = acpi_evaluate_integer(handle, "TCMD", &input, &output);
	if (ACPI_SUCCESS(status))
		*value = output;
	return status;
}