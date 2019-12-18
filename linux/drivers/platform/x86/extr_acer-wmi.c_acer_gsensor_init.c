#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  union acpi_object {int dummy; } acpi_object ;
struct acpi_buffer {int length; union acpi_object* pointer; } ;
typedef  int /*<<< orphan*/  out_obj ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  gsensor_handle ; 

__attribute__((used)) static int acer_gsensor_init(void)
{
	acpi_status status;
	struct acpi_buffer output;
	union acpi_object out_obj;

	output.length = sizeof(out_obj);
	output.pointer = &out_obj;
	status = acpi_evaluate_object(gsensor_handle, "_INI", NULL, &output);
	if (ACPI_FAILURE(status))
		return -1;

	return 0;
}