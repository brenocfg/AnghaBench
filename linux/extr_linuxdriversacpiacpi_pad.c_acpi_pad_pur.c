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
struct TYPE_6__ {int count; TYPE_2__* elements; } ;
union acpi_object {scalar_t__ type; TYPE_3__ package; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/  length; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_4__ {int value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

__attribute__((used)) static int acpi_pad_pur(acpi_handle handle)
{
	struct acpi_buffer buffer = {ACPI_ALLOCATE_BUFFER, NULL};
	union acpi_object *package;
	int num = -1;

	if (ACPI_FAILURE(acpi_evaluate_object(handle, "_PUR", NULL, &buffer)))
		return num;

	if (!buffer.length || !buffer.pointer)
		return num;

	package = buffer.pointer;

	if (package->type == ACPI_TYPE_PACKAGE &&
		package->package.count == 2 &&
		package->package.elements[0].integer.value == 1) /* rev 1 */

		num = package->package.elements[1].integer.value;

	kfree(buffer.pointer);
	return num;
}