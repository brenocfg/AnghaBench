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
struct TYPE_2__ {scalar_t__ type; } ;
union acpi_operand_object {TYPE_1__ common; } ;
struct acpi_walk_state {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ut_copy_ipackage_to_ipackage (union acpi_operand_object*,union acpi_operand_object*,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ut_copy_simple_object (union acpi_operand_object*,union acpi_operand_object*) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_copy_iobject_to_iobject ; 

acpi_status
acpi_ut_copy_iobject_to_iobject(union acpi_operand_object *source_desc,
				union acpi_operand_object **dest_desc,
				struct acpi_walk_state *walk_state)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ut_copy_iobject_to_iobject);

	/* Create the top level object */

	*dest_desc = acpi_ut_create_internal_object(source_desc->common.type);
	if (!*dest_desc) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/* Copy the object and possible subobjects */

	if (source_desc->common.type == ACPI_TYPE_PACKAGE) {
		status =
		    acpi_ut_copy_ipackage_to_ipackage(source_desc, *dest_desc,
						      walk_state);
	} else {
		status = acpi_ut_copy_simple_object(source_desc, *dest_desc);
	}

	/* Delete the allocated object if copy failed */

	if (ACPI_FAILURE(status)) {
		acpi_ut_remove_reference(*dest_desc);
	}

	return_ACPI_STATUS(status);
}