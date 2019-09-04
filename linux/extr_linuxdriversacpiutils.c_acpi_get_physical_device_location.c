#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* elements; int /*<<< orphan*/  count; } ;
union acpi_object {scalar_t__ type; TYPE_3__ package; } ;
struct acpi_pld_info {int dummy; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/  pointer; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_PLD_REV1_BUFFER_SIZE ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int /*<<< orphan*/  acpi_decode_pld_buffer (int /*<<< orphan*/ ,scalar_t__,struct acpi_pld_info**) ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

acpi_status
acpi_get_physical_device_location(acpi_handle handle, struct acpi_pld_info **pld)
{
	acpi_status status;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *output;

	status = acpi_evaluate_object(handle, "_PLD", NULL, &buffer);

	if (ACPI_FAILURE(status))
		return status;

	output = buffer.pointer;

	if (!output || output->type != ACPI_TYPE_PACKAGE
	    || !output->package.count
	    || output->package.elements[0].type != ACPI_TYPE_BUFFER
	    || output->package.elements[0].buffer.length < ACPI_PLD_REV1_BUFFER_SIZE) {
		status = AE_TYPE;
		goto out;
	}

	status = acpi_decode_pld_buffer(
			output->package.elements[0].buffer.pointer,
			output->package.elements[0].buffer.length,
			pld);

out:
	kfree(buffer.pointer);
	return status;
}