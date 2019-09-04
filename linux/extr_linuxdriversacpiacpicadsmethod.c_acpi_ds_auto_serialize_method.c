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
struct TYPE_5__ {struct acpi_namespace_node* node; } ;
union acpi_parse_object {TYPE_2__ common; } ;
struct TYPE_6__ {int /*<<< orphan*/  aml_length; int /*<<< orphan*/  aml_start; } ;
union acpi_operand_object {TYPE_3__ method; } ;
struct acpi_walk_state {int /*<<< orphan*/  descending_callback; } ;
struct TYPE_4__ {int /*<<< orphan*/  integer; } ;
struct acpi_namespace_node {int /*<<< orphan*/  owner_id; TYPE_1__ name; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AML_METHOD_OP ; 
 struct acpi_walk_state* acpi_ds_create_walk_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ds_delete_walk_state (struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ds_detect_named_opcodes ; 
 int /*<<< orphan*/  acpi_ds_init_aml_walk (struct acpi_walk_state*,union acpi_parse_object*,struct acpi_namespace_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 union acpi_parse_object* acpi_ps_alloc_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ps_delete_parse_tree (union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ps_free_op (union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ps_parse_aml (struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ps_set_name (union acpi_parse_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  ds_auto_serialize_method ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_auto_serialize_method(struct acpi_namespace_node *node,
			      union acpi_operand_object *obj_desc)
{
	acpi_status status;
	union acpi_parse_object *op = NULL;
	struct acpi_walk_state *walk_state;

	ACPI_FUNCTION_TRACE_PTR(ds_auto_serialize_method, node);

	ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
			  "Method auto-serialization parse [%4.4s] %p\n",
			  acpi_ut_get_node_name(node), node));

	/* Create/Init a root op for the method parse tree */

	op = acpi_ps_alloc_op(AML_METHOD_OP, obj_desc->method.aml_start);
	if (!op) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	acpi_ps_set_name(op, node->name.integer);
	op->common.node = node;

	/* Create and initialize a new walk state */

	walk_state =
	    acpi_ds_create_walk_state(node->owner_id, NULL, NULL, NULL);
	if (!walk_state) {
		acpi_ps_free_op(op);
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	status = acpi_ds_init_aml_walk(walk_state, op, node,
				       obj_desc->method.aml_start,
				       obj_desc->method.aml_length, NULL, 0);
	if (ACPI_FAILURE(status)) {
		acpi_ds_delete_walk_state(walk_state);
		acpi_ps_free_op(op);
		return_ACPI_STATUS(status);
	}

	walk_state->descending_callback = acpi_ds_detect_named_opcodes;

	/* Parse the method, scan for creation of named objects */

	status = acpi_ps_parse_aml(walk_state);

	acpi_ps_delete_parse_tree(op);
	return_ACPI_STATUS(status);
}