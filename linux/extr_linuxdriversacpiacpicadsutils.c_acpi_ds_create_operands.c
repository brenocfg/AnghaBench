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
struct TYPE_2__ {union acpi_parse_object* next; } ;
union acpi_parse_object {TYPE_1__ common; } ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct acpi_walk_state {int num_operands; scalar_t__ operand_index; int /*<<< orphan*/ ** operands; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int ACPI_OBJ_NUM_OPERANDS ; 
 int /*<<< orphan*/  AE_BAD_DATA ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ds_create_operand (struct acpi_walk_state*,union acpi_parse_object*,int) ; 
 int /*<<< orphan*/  acpi_ds_obj_stack_pop_and_delete (int,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  ds_create_operands ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_create_operands(struct acpi_walk_state *walk_state,
			union acpi_parse_object *first_arg)
{
	acpi_status status = AE_OK;
	union acpi_parse_object *arg;
	union acpi_parse_object *arguments[ACPI_OBJ_NUM_OPERANDS];
	u32 arg_count = 0;
	u32 index = walk_state->num_operands;
	u32 i;

	ACPI_FUNCTION_TRACE_PTR(ds_create_operands, first_arg);

	/* Get all arguments in the list */

	arg = first_arg;
	while (arg) {
		if (index >= ACPI_OBJ_NUM_OPERANDS) {
			return_ACPI_STATUS(AE_BAD_DATA);
		}

		arguments[index] = arg;
		walk_state->operands[index] = NULL;

		/* Move on to next argument, if any */

		arg = arg->common.next;
		arg_count++;
		index++;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "NumOperands %d, ArgCount %d, Index %d\n",
			  walk_state->num_operands, arg_count, index));

	/* Create the interpreter arguments, in reverse order */

	index--;
	for (i = 0; i < arg_count; i++) {
		arg = arguments[index];
		walk_state->operand_index = (u8)index;

		status = acpi_ds_create_operand(walk_state, arg, index);
		if (ACPI_FAILURE(status)) {
			goto cleanup;
		}

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "Created Arg #%u (%p) %u args total\n",
				  index, arg, arg_count));
		index--;
	}

	return_ACPI_STATUS(status);

cleanup:
	/*
	 * We must undo everything done above; meaning that we must
	 * pop everything off of the operand stack and delete those
	 * objects
	 */
	acpi_ds_obj_stack_pop_and_delete(arg_count, walk_state);

	ACPI_EXCEPTION((AE_INFO, status, "While creating Arg %u", index));
	return_ACPI_STATUS(status);
}