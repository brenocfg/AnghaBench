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
struct TYPE_4__ {union acpi_operand_object* object; int /*<<< orphan*/  class; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
union acpi_operand_object {TYPE_2__ reference; TYPE_1__ common; } ;
struct acpi_walk_state {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
#define  ACPI_DESC_TYPE_NAMED 132 
#define  ACPI_DESC_TYPE_OPERAND 131 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 int ACPI_GET_DESCRIPTOR_TYPE (union acpi_operand_object*) ; 
#define  ACPI_REFCLASS_ARG 130 
#define  ACPI_REFCLASS_DEBUG 129 
#define  ACPI_REFCLASS_LOCAL 128 
 int /*<<< orphan*/  ACPI_REFCLASS_REFOF ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_REFERENCE ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_get_object_reference ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_get_object_reference(union acpi_operand_object *obj_desc,
			     union acpi_operand_object **return_desc,
			     struct acpi_walk_state *walk_state)
{
	union acpi_operand_object *reference_obj;
	union acpi_operand_object *referenced_obj;

	ACPI_FUNCTION_TRACE_PTR(ex_get_object_reference, obj_desc);

	*return_desc = NULL;

	switch (ACPI_GET_DESCRIPTOR_TYPE(obj_desc)) {
	case ACPI_DESC_TYPE_OPERAND:

		if (obj_desc->common.type != ACPI_TYPE_LOCAL_REFERENCE) {
			return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		}

		/*
		 * Must be a reference to a Local or Arg
		 */
		switch (obj_desc->reference.class) {
		case ACPI_REFCLASS_LOCAL:
		case ACPI_REFCLASS_ARG:
		case ACPI_REFCLASS_DEBUG:

			/* The referenced object is the pseudo-node for the local/arg */

			referenced_obj = obj_desc->reference.object;
			break;

		default:

			ACPI_ERROR((AE_INFO, "Invalid Reference Class 0x%2.2X",
				    obj_desc->reference.class));
			return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		}
		break;

	case ACPI_DESC_TYPE_NAMED:
		/*
		 * A named reference that has already been resolved to a Node
		 */
		referenced_obj = obj_desc;
		break;

	default:

		ACPI_ERROR((AE_INFO, "Invalid descriptor type 0x%X",
			    ACPI_GET_DESCRIPTOR_TYPE(obj_desc)));
		return_ACPI_STATUS(AE_TYPE);
	}

	/* Create a new reference object */

	reference_obj =
	    acpi_ut_create_internal_object(ACPI_TYPE_LOCAL_REFERENCE);
	if (!reference_obj) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	reference_obj->reference.class = ACPI_REFCLASS_REFOF;
	reference_obj->reference.object = referenced_obj;
	*return_desc = reference_obj;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Object %p Type [%s], returning Reference %p\n",
			  obj_desc, acpi_ut_get_object_type_name(obj_desc),
			  *return_desc));

	return_ACPI_STATUS(AE_OK);
}