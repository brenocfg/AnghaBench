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
struct TYPE_2__ {struct acpi_namespace_node* node; union acpi_parse_object* parent; } ;
union acpi_parse_object {TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct acpi_parse_state {struct acpi_namespace_node* start_node; union acpi_parse_object* start_op; int /*<<< orphan*/ * pkg_end; int /*<<< orphan*/ * aml_end; int /*<<< orphan*/ * aml_start; int /*<<< orphan*/ * aml; } ;
struct acpi_walk_state {int /*<<< orphan*/  params; int /*<<< orphan*/  method_desc; struct acpi_namespace_node* method_node; int /*<<< orphan*/  walk_type; struct acpi_parse_state parser_state; int /*<<< orphan*/ * caller_return_desc; int /*<<< orphan*/  pass_number; int /*<<< orphan*/ * next_op; } ;
struct acpi_namespace_node {int /*<<< orphan*/  type; } ;
struct acpi_evaluate_info {int /*<<< orphan*/  return_object; int /*<<< orphan*/  parameters; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_METHOD_NUM_ARGS ; 
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  ACPI_WALK_METHOD ; 
 int /*<<< orphan*/  acpi_ds_init_callbacks (struct acpi_walk_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ds_method_data_init_args (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ds_scope_stack_push (struct acpi_namespace_node*,int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ps_init_scope (struct acpi_parse_state*,union acpi_parse_object*) ; 
 int /*<<< orphan*/  ds_init_aml_walk ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_init_aml_walk(struct acpi_walk_state *walk_state,
		      union acpi_parse_object *op,
		      struct acpi_namespace_node *method_node,
		      u8 * aml_start,
		      u32 aml_length,
		      struct acpi_evaluate_info *info, u8 pass_number)
{
	acpi_status status;
	struct acpi_parse_state *parser_state = &walk_state->parser_state;
	union acpi_parse_object *extra_op;

	ACPI_FUNCTION_TRACE(ds_init_aml_walk);

	walk_state->parser_state.aml =
	    walk_state->parser_state.aml_start = aml_start;
	walk_state->parser_state.aml_end =
	    walk_state->parser_state.pkg_end = aml_start + aml_length;

	/* The next_op of the next_walk will be the beginning of the method */

	walk_state->next_op = NULL;
	walk_state->pass_number = pass_number;

	if (info) {
		walk_state->params = info->parameters;
		walk_state->caller_return_desc = &info->return_object;
	}

	status = acpi_ps_init_scope(&walk_state->parser_state, op);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	if (method_node) {
		walk_state->parser_state.start_node = method_node;
		walk_state->walk_type = ACPI_WALK_METHOD;
		walk_state->method_node = method_node;
		walk_state->method_desc =
		    acpi_ns_get_attached_object(method_node);

		/* Push start scope on scope stack and make it current  */

		status =
		    acpi_ds_scope_stack_push(method_node, ACPI_TYPE_METHOD,
					     walk_state);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}

		/* Init the method arguments */

		status = acpi_ds_method_data_init_args(walk_state->params,
						       ACPI_METHOD_NUM_ARGS,
						       walk_state);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}
	} else {
		/*
		 * Setup the current scope.
		 * Find a Named Op that has a namespace node associated with it.
		 * search upwards from this Op. Current scope is the first
		 * Op with a namespace node.
		 */
		extra_op = parser_state->start_op;
		while (extra_op && !extra_op->common.node) {
			extra_op = extra_op->common.parent;
		}

		if (!extra_op) {
			parser_state->start_node = NULL;
		} else {
			parser_state->start_node = extra_op->common.node;
		}

		if (parser_state->start_node) {

			/* Push start scope on scope stack and make it current  */

			status =
			    acpi_ds_scope_stack_push(parser_state->start_node,
						     parser_state->start_node->
						     type, walk_state);
			if (ACPI_FAILURE(status)) {
				return_ACPI_STATUS(status);
			}
		}
	}

	status = acpi_ds_init_callbacks(walk_state, pass_number);
	return_ACPI_STATUS(status);
}