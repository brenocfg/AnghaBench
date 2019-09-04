#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {char* name; } ;
struct TYPE_18__ {TYPE_8__ value; TYPE_7__* parent; struct acpi_namespace_node* node; } ;
union acpi_parse_object {TYPE_9__ common; } ;
struct TYPE_12__ {int param_count; } ;
union acpi_operand_object {TYPE_3__ method; } ;
typedef  scalar_t__ u8 ;
struct TYPE_10__ {scalar_t__* aml; } ;
struct acpi_walk_state {int arg_count; int parse_flags; int /*<<< orphan*/  scope_info; TYPE_5__* op; TYPE_1__ parser_state; int /*<<< orphan*/  arg_types; } ;
struct acpi_parse_state {scalar_t__* aml; } ;
struct TYPE_11__ {int /*<<< orphan*/  ascii; } ;
struct acpi_namespace_node {scalar_t__ type; TYPE_2__ name; } ;
typedef  scalar_t__ acpi_status ;
struct TYPE_15__ {scalar_t__ aml_opcode; } ;
struct TYPE_16__ {TYPE_6__ common; } ;
struct TYPE_13__ {scalar_t__ aml_opcode; } ;
struct TYPE_14__ {TYPE_4__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR_NAMESPACE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 int ACPI_NS_DONT_OPEN_SCOPE ; 
 int ACPI_NS_SEARCH_PARENT ; 
 int ACPI_PARSE_EXECUTE ; 
 int ACPI_PARSE_MODE_MASK ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 scalar_t__ ACPI_TYPE_METHOD ; 
 scalar_t__ AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ AE_NO_MEMORY ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AML_CONDITIONAL_REF_OF_OP ; 
 int /*<<< orphan*/  AML_INT_METHODCALL_OP ; 
 int /*<<< orphan*/  AML_INT_NAMEPATH_OP ; 
 scalar_t__ AML_PACKAGE_OP ; 
 scalar_t__ AML_VARIABLE_PACKAGE_OP ; 
 scalar_t__ ARGP_SUPERNAME ; 
 scalar_t__ ARGP_TARGET ; 
 scalar_t__ GET_CURRENT_ARG_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_ds_method_error (scalar_t__,struct acpi_walk_state*) ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 scalar_t__ acpi_ns_lookup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct acpi_namespace_node**) ; 
 union acpi_parse_object* acpi_ps_alloc_op (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_ps_append_arg (union acpi_parse_object*,union acpi_parse_object*) ; 
 char* acpi_ps_get_next_namestring (struct acpi_parse_state*) ; 
 int /*<<< orphan*/  acpi_ps_init_op (union acpi_parse_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_get_next_namepath ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

acpi_status
acpi_ps_get_next_namepath(struct acpi_walk_state *walk_state,
			  struct acpi_parse_state *parser_state,
			  union acpi_parse_object *arg, u8 possible_method_call)
{
	acpi_status status;
	char *path;
	union acpi_parse_object *name_op;
	union acpi_operand_object *method_desc;
	struct acpi_namespace_node *node;
	u8 *start = parser_state->aml;

	ACPI_FUNCTION_TRACE(ps_get_next_namepath);

	path = acpi_ps_get_next_namestring(parser_state);
	acpi_ps_init_op(arg, AML_INT_NAMEPATH_OP);

	/* Null path case is allowed, just exit */

	if (!path) {
		arg->common.value.name = path;
		return_ACPI_STATUS(AE_OK);
	}

	/*
	 * Lookup the name in the internal namespace, starting with the current
	 * scope. We don't want to add anything new to the namespace here,
	 * however, so we use MODE_EXECUTE.
	 * Allow searching of the parent tree, but don't open a new scope -
	 * we just want to lookup the object (must be mode EXECUTE to perform
	 * the upsearch)
	 */
	status = acpi_ns_lookup(walk_state->scope_info, path,
				ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
				ACPI_NS_SEARCH_PARENT | ACPI_NS_DONT_OPEN_SCOPE,
				NULL, &node);

	/*
	 * If this name is a control method invocation, we must
	 * setup the method call
	 */
	if (ACPI_SUCCESS(status) &&
	    possible_method_call && (node->type == ACPI_TYPE_METHOD)) {
		if ((GET_CURRENT_ARG_TYPE(walk_state->arg_types) ==
		     ARGP_SUPERNAME)
		    || (GET_CURRENT_ARG_TYPE(walk_state->arg_types) ==
			ARGP_TARGET)) {
			/*
			 * acpi_ps_get_next_namestring has increased the AML pointer past
			 * the method invocation namestring, so we need to restore the
			 * saved AML pointer back to the original method invocation
			 * namestring.
			 */
			walk_state->parser_state.aml = start;
			walk_state->arg_count = 1;
			acpi_ps_init_op(arg, AML_INT_METHODCALL_OP);
		}

		/* This name is actually a control method invocation */

		method_desc = acpi_ns_get_attached_object(node);
		ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
				  "Control Method invocation %4.4s - %p Desc %p Path=%p\n",
				  node->name.ascii, node, method_desc, path));

		name_op = acpi_ps_alloc_op(AML_INT_NAMEPATH_OP, start);
		if (!name_op) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}

		/* Change Arg into a METHOD CALL and attach name to it */

		acpi_ps_init_op(arg, AML_INT_METHODCALL_OP);
		name_op->common.value.name = path;

		/* Point METHODCALL/NAME to the METHOD Node */

		name_op->common.node = node;
		acpi_ps_append_arg(arg, name_op);

		if (!method_desc) {
			ACPI_ERROR((AE_INFO,
				    "Control Method %p has no attached object",
				    node));
			return_ACPI_STATUS(AE_AML_INTERNAL);
		}

		ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
				  "Control Method - %p Args %X\n",
				  node, method_desc->method.param_count));

		/* Get the number of arguments to expect */

		walk_state->arg_count = method_desc->method.param_count;
		return_ACPI_STATUS(AE_OK);
	}

	/*
	 * Special handling if the name was not found during the lookup -
	 * some not_found cases are allowed
	 */
	if (status == AE_NOT_FOUND) {

		/* 1) not_found is ok during load pass 1/2 (allow forward references) */

		if ((walk_state->parse_flags & ACPI_PARSE_MODE_MASK) !=
		    ACPI_PARSE_EXECUTE) {
			status = AE_OK;
		}

		/* 2) not_found during a cond_ref_of(x) is ok by definition */

		else if (walk_state->op->common.aml_opcode ==
			 AML_CONDITIONAL_REF_OF_OP) {
			status = AE_OK;
		}

		/*
		 * 3) not_found while building a Package is ok at this point, we
		 * may flag as an error later if slack mode is not enabled.
		 * (Some ASL code depends on allowing this behavior)
		 */
		else if ((arg->common.parent) &&
			 ((arg->common.parent->common.aml_opcode ==
			   AML_PACKAGE_OP)
			  || (arg->common.parent->common.aml_opcode ==
			      AML_VARIABLE_PACKAGE_OP))) {
			status = AE_OK;
		}
	}

	/* Final exception check (may have been changed from code above) */

	if (ACPI_FAILURE(status)) {
		ACPI_ERROR_NAMESPACE(walk_state->scope_info, path, status);

		if ((walk_state->parse_flags & ACPI_PARSE_MODE_MASK) ==
		    ACPI_PARSE_EXECUTE) {

			/* Report a control method execution error */

			status = acpi_ds_method_error(status, walk_state);
		}
	}

	/* Save the namepath */

	arg->common.value.name = path;
	return_ACPI_STATUS(status);
}