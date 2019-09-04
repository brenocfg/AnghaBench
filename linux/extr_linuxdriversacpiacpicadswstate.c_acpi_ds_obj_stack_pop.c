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
typedef  scalar_t__ u32 ;
struct acpi_walk_state {size_t num_operands; int /*<<< orphan*/ ** operands; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_STACK_UNDERFLOW ; 
 int /*<<< orphan*/  ds_obj_stack_pop ; 

acpi_status
acpi_ds_obj_stack_pop(u32 pop_count, struct acpi_walk_state *walk_state)
{
	u32 i;

	ACPI_FUNCTION_NAME(ds_obj_stack_pop);

	for (i = 0; i < pop_count; i++) {

		/* Check for stack underflow */

		if (walk_state->num_operands == 0) {
			ACPI_ERROR((AE_INFO,
				    "Object stack underflow! Count=%X State=%p #Ops=%u",
				    pop_count, walk_state,
				    walk_state->num_operands));
			return (AE_STACK_UNDERFLOW);
		}

		/* Just set the stack entry to null */

		walk_state->num_operands--;
		walk_state->operands[walk_state->num_operands] = NULL;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Count=%X State=%p #Ops=%u\n",
			  pop_count, walk_state, walk_state->num_operands));

	return (AE_OK);
}