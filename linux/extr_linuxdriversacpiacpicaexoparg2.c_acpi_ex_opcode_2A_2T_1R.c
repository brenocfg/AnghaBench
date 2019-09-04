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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
union acpi_operand_object {TYPE_1__ integer; } ;
struct acpi_walk_state {int opcode; union acpi_operand_object* result_obj; union acpi_operand_object** operands; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_STR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AE_AML_BAD_OPCODE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
#define  AML_DIVIDE_OP 128 
 int /*<<< orphan*/  acpi_ex_store (union acpi_operand_object*,union acpi_operand_object*,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ps_get_opcode_name (int) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_divide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_opcode_2A_2T_1R ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ex_opcode_2A_2T_1R(struct acpi_walk_state *walk_state)
{
	union acpi_operand_object **operand = &walk_state->operands[0];
	union acpi_operand_object *return_desc1 = NULL;
	union acpi_operand_object *return_desc2 = NULL;
	acpi_status status;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_2A_2T_1R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	/* Execute the opcode */

	switch (walk_state->opcode) {
	case AML_DIVIDE_OP:

		/* Divide (Dividend, Divisor, remainder_result quotient_result) */

		return_desc1 =
		    acpi_ut_create_internal_object(ACPI_TYPE_INTEGER);
		if (!return_desc1) {
			status = AE_NO_MEMORY;
			goto cleanup;
		}

		return_desc2 =
		    acpi_ut_create_internal_object(ACPI_TYPE_INTEGER);
		if (!return_desc2) {
			status = AE_NO_MEMORY;
			goto cleanup;
		}

		/* Quotient to return_desc1, remainder to return_desc2 */

		status = acpi_ut_divide(operand[0]->integer.value,
					operand[1]->integer.value,
					&return_desc1->integer.value,
					&return_desc2->integer.value);
		if (ACPI_FAILURE(status)) {
			goto cleanup;
		}
		break;

	default:

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));

		status = AE_AML_BAD_OPCODE;
		goto cleanup;
	}

	/* Store the results to the target reference operands */

	status = acpi_ex_store(return_desc2, operand[2], walk_state);
	if (ACPI_FAILURE(status)) {
		goto cleanup;
	}

	status = acpi_ex_store(return_desc1, operand[3], walk_state);
	if (ACPI_FAILURE(status)) {
		goto cleanup;
	}

cleanup:
	/*
	 * Since the remainder is not returned indirectly, remove a reference to
	 * it. Only the quotient is returned indirectly.
	 */
	acpi_ut_remove_reference(return_desc2);

	if (ACPI_FAILURE(status)) {

		/* Delete the return object */

		acpi_ut_remove_reference(return_desc1);
	}

	/* Save return object (the remainder) on success */

	else {
		walk_state->result_obj = return_desc1;
	}

	return_ACPI_STATUS(status);
}