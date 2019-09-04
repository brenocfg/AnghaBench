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

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (union acpi_operand_object*) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  acpi_gbl_operand_cache ; 
 int /*<<< orphan*/  acpi_os_release_object (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_descriptor_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  return_VOID ; 
 int /*<<< orphan*/  ut_delete_object_desc ; 

void acpi_ut_delete_object_desc(union acpi_operand_object *object)
{
	ACPI_FUNCTION_TRACE_PTR(ut_delete_object_desc, object);

	/* Object must be of type union acpi_operand_object */

	if (ACPI_GET_DESCRIPTOR_TYPE(object) != ACPI_DESC_TYPE_OPERAND) {
		ACPI_ERROR((AE_INFO,
			    "%p is not an ACPI Operand object [%s]", object,
			    acpi_ut_get_descriptor_name(object)));
		return_VOID;
	}

	(void)acpi_os_release_object(acpi_gbl_operand_cache, object);
	return_VOID;
}