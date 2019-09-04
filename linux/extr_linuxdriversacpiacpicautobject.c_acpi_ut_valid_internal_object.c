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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
#define  ACPI_DESC_TYPE_OPERAND 128 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int ACPI_GET_DESCRIPTOR_TYPE (void*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ut_get_descriptor_name (void*) ; 
 int /*<<< orphan*/  ut_valid_internal_object ; 

u8 acpi_ut_valid_internal_object(void *object)
{

	ACPI_FUNCTION_NAME(ut_valid_internal_object);

	/* Check for a null pointer */

	if (!object) {
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "**** Null Object Ptr\n"));
		return (FALSE);
	}

	/* Check the descriptor type field */

	switch (ACPI_GET_DESCRIPTOR_TYPE(object)) {
	case ACPI_DESC_TYPE_OPERAND:

		/* The object appears to be a valid union acpi_operand_object */

		return (TRUE);

	default:

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "%p is not an ACPI operand obj [%s]\n",
				  object, acpi_ut_get_descriptor_name(object)));
		break;
	}

	return (FALSE);
}