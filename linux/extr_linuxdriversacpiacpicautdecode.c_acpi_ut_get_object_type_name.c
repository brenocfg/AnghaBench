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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
union acpi_operand_object {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_descriptor_name (union acpi_operand_object*) ; 
 char* acpi_ut_get_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_STR (char*) ; 
 int /*<<< orphan*/  ut_get_object_type_name ; 

const char *acpi_ut_get_object_type_name(union acpi_operand_object *obj_desc)
{
	ACPI_FUNCTION_TRACE(ut_get_object_type_name);

	if (!obj_desc) {
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Null Object Descriptor\n"));
		return_STR("[NULL Object Descriptor]");
	}

	/* These descriptor types share a common area */

	if ((ACPI_GET_DESCRIPTOR_TYPE(obj_desc) != ACPI_DESC_TYPE_OPERAND) &&
	    (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) != ACPI_DESC_TYPE_NAMED)) {
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Invalid object descriptor type: 0x%2.2X [%s] (%p)\n",
				  ACPI_GET_DESCRIPTOR_TYPE(obj_desc),
				  acpi_ut_get_descriptor_name(obj_desc),
				  obj_desc));

		return_STR("Invalid object");
	}

	return_STR(acpi_ut_get_type_name(obj_desc->common.type));
}