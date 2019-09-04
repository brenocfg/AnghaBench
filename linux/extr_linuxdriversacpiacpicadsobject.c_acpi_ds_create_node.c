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
struct TYPE_6__ {int /*<<< orphan*/  arg; } ;
struct TYPE_5__ {TYPE_3__ value; } ;
union acpi_parse_object {TYPE_2__ common; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
union acpi_operand_object {TYPE_1__ common; } ;
struct acpi_walk_state {int dummy; } ;
struct acpi_namespace_node {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ds_build_internal_object (struct acpi_walk_state*,int /*<<< orphan*/ ,union acpi_operand_object**) ; 
 int /*<<< orphan*/  acpi_ns_attach_object (struct acpi_namespace_node*,union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ds_create_node ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_create_node(struct acpi_walk_state *walk_state,
		    struct acpi_namespace_node *node,
		    union acpi_parse_object *op)
{
	acpi_status status;
	union acpi_operand_object *obj_desc;

	ACPI_FUNCTION_TRACE_PTR(ds_create_node, op);

	/*
	 * Because of the execution pass through the non-control-method
	 * parts of the table, we can arrive here twice. Only init
	 * the named object node the first time through
	 */
	if (acpi_ns_get_attached_object(node)) {
		return_ACPI_STATUS(AE_OK);
	}

	if (!op->common.value.arg) {

		/* No arguments, there is nothing to do */

		return_ACPI_STATUS(AE_OK);
	}

	/* Build an internal object for the argument(s) */

	status =
	    acpi_ds_build_internal_object(walk_state, op->common.value.arg,
					  &obj_desc);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Re-type the object according to its argument */

	node->type = obj_desc->common.type;

	/* Attach obj to node */

	status = acpi_ns_attach_object(node, obj_desc, node->type);

	/* Remove local reference to the object */

	acpi_ut_remove_reference(obj_desc);
	return_ACPI_STATUS(status);
}