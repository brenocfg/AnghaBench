#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct acpi_walk_state {TYPE_2__* local_variables; TYPE_1__* arguments; } ;
struct TYPE_6__ {size_t integer; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; void* type; void* descriptor_type; TYPE_3__ name; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; void* type; void* descriptor_type; TYPE_3__ name; } ;

/* Variables and functions */
 void* ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 size_t ACPI_METHOD_NUM_ARGS ; 
 size_t ACPI_METHOD_NUM_LOCALS ; 
 int /*<<< orphan*/  ACPI_MOVE_32_TO_32 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ANOBJ_METHOD_ARG ; 
 int /*<<< orphan*/  ANOBJ_METHOD_LOCAL ; 
 int /*<<< orphan*/  NAMEOF_ARG_NTE ; 
 int /*<<< orphan*/  NAMEOF_LOCAL_NTE ; 
 int /*<<< orphan*/  ds_method_data_init ; 
 int /*<<< orphan*/  return_VOID ; 

void acpi_ds_method_data_init(struct acpi_walk_state *walk_state)
{
	u32 i;

	ACPI_FUNCTION_TRACE(ds_method_data_init);

	/* Init the method arguments */

	for (i = 0; i < ACPI_METHOD_NUM_ARGS; i++) {
		ACPI_MOVE_32_TO_32(&walk_state->arguments[i].name,
				   NAMEOF_ARG_NTE);

		walk_state->arguments[i].name.integer |= (i << 24);
		walk_state->arguments[i].descriptor_type = ACPI_DESC_TYPE_NAMED;
		walk_state->arguments[i].type = ACPI_TYPE_ANY;
		walk_state->arguments[i].flags = ANOBJ_METHOD_ARG;
	}

	/* Init the method locals */

	for (i = 0; i < ACPI_METHOD_NUM_LOCALS; i++) {
		ACPI_MOVE_32_TO_32(&walk_state->local_variables[i].name,
				   NAMEOF_LOCAL_NTE);

		walk_state->local_variables[i].name.integer |= (i << 24);
		walk_state->local_variables[i].descriptor_type =
		    ACPI_DESC_TYPE_NAMED;
		walk_state->local_variables[i].type = ACPI_TYPE_ANY;
		walk_state->local_variables[i].flags = ANOBJ_METHOD_LOCAL;
	}

	return_VOID;
}