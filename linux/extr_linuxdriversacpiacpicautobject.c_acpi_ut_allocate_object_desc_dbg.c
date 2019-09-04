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
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_ALLOCATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_ERROR (char const*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SET_DESCRIPTOR_TYPE (union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_operand_cache ; 
 union acpi_operand_object* acpi_os_acquire_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_PTR (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ut_allocate_object_desc_dbg ; 

void *acpi_ut_allocate_object_desc_dbg(const char *module_name,
				       u32 line_number, u32 component_id)
{
	union acpi_operand_object *object;

	ACPI_FUNCTION_TRACE(ut_allocate_object_desc_dbg);

	object = acpi_os_acquire_object(acpi_gbl_operand_cache);
	if (!object) {
		ACPI_ERROR((module_name, line_number,
			    "Could not allocate an object descriptor"));

		return_PTR(NULL);
	}

	/* Mark the descriptor type */

	ACPI_SET_DESCRIPTOR_TYPE(object, ACPI_DESC_TYPE_OPERAND);

	ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS, "%p Size %X\n",
			  object, (u32) sizeof(union acpi_operand_object)));

	return_PTR(object);
}