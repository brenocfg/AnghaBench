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
struct TYPE_4__ {int /*<<< orphan*/  elements; scalar_t__ count; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
union acpi_operand_object {TYPE_2__ package; TYPE_1__ common; } ;
struct acpi_walk_state {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ut_copy_ielement_to_ielement ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_walk_package_tree (union acpi_operand_object*,union acpi_operand_object*,int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_copy_ipackage_to_ipackage ; 

__attribute__((used)) static acpi_status
acpi_ut_copy_ipackage_to_ipackage(union acpi_operand_object *source_obj,
				  union acpi_operand_object *dest_obj,
				  struct acpi_walk_state *walk_state)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ut_copy_ipackage_to_ipackage);

	dest_obj->common.type = source_obj->common.type;
	dest_obj->common.flags = source_obj->common.flags;
	dest_obj->package.count = source_obj->package.count;

	/*
	 * Create the object array and walk the source package tree
	 */
	dest_obj->package.elements = ACPI_ALLOCATE_ZEROED(((acpi_size)
							   source_obj->package.
							   count +
							   1) * sizeof(void *));
	if (!dest_obj->package.elements) {
		ACPI_ERROR((AE_INFO, "Package allocation failure"));
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/*
	 * Copy the package element-by-element by walking the package "tree".
	 * This handles nested packages of arbitrary depth.
	 */
	status = acpi_ut_walk_package_tree(source_obj, dest_obj,
					   acpi_ut_copy_ielement_to_ielement,
					   walk_state);
	if (ACPI_FAILURE(status)) {

		/* On failure, delete the destination package object */

		acpi_ut_remove_reference(dest_obj);
	}

	return_ACPI_STATUS(status);
}