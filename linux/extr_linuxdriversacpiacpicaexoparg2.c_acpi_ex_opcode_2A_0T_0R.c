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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {int opcode; union acpi_operand_object** operands; } ;
struct acpi_namespace_node {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_STR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_BAD_OPCODE ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_NOTIFY_OP 128 
 int /*<<< orphan*/  acpi_ev_is_notify_object (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ev_queue_notify_request (struct acpi_namespace_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ps_get_opcode_name (int) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_opcode_2A_0T_0R ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ex_opcode_2A_0T_0R(struct acpi_walk_state *walk_state)
{
	union acpi_operand_object **operand = &walk_state->operands[0];
	struct acpi_namespace_node *node;
	u32 value;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_2A_0T_0R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	/* Examine the opcode */

	switch (walk_state->opcode) {
	case AML_NOTIFY_OP:	/* Notify (notify_object, notify_value) */

		/* The first operand is a namespace node */

		node = (struct acpi_namespace_node *)operand[0];

		/* Second value is the notify value */

		value = (u32) operand[1]->integer.value;

		/* Are notifies allowed on this object? */

		if (!acpi_ev_is_notify_object(node)) {
			ACPI_ERROR((AE_INFO,
				    "Unexpected notify object type [%s]",
				    acpi_ut_get_type_name(node->type)));

			status = AE_AML_OPERAND_TYPE;
			break;
		}

		/*
		 * Dispatch the notify to the appropriate handler
		 * NOTE: the request is queued for execution after this method
		 * completes. The notify handlers are NOT invoked synchronously
		 * from this thread -- because handlers may in turn run other
		 * control methods.
		 */
		status = acpi_ev_queue_notify_request(node, value);
		break;

	default:

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));
		status = AE_AML_BAD_OPCODE;
	}

	return_ACPI_STATUS(status);
}