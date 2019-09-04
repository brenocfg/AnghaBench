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
struct TYPE_2__ {int /*<<< orphan*/  reference_count; } ;
union acpi_operand_object {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_ALLOCATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REF_INCREMENT ; 
 int /*<<< orphan*/  acpi_ut_update_object_reference (union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_valid_internal_object (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ut_add_reference ; 

void acpi_ut_add_reference(union acpi_operand_object *object)
{

	ACPI_FUNCTION_NAME(ut_add_reference);

	/* Ensure that we have a valid object */

	if (!acpi_ut_valid_internal_object(object)) {
		return;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
			  "Obj %p Current Refs=%X [To Be Incremented]\n",
			  object, object->common.reference_count));

	/* Increment the reference count */

	(void)acpi_ut_update_object_reference(object, REF_INCREMENT);
	return;
}