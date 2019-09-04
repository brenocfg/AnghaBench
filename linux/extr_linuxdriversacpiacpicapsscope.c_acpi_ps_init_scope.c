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
typedef  union acpi_parse_object {int dummy; } acpi_parse_object ;
struct TYPE_3__ {int /*<<< orphan*/  pkg_end; int /*<<< orphan*/  arg_end; int /*<<< orphan*/  arg_count; union acpi_parse_object* op; } ;
struct TYPE_4__ {int /*<<< orphan*/  descriptor_type; } ;
union acpi_generic_state {TYPE_1__ parse_scope; TYPE_2__ common; } ;
struct acpi_parse_state {union acpi_parse_object* start_op; union acpi_generic_state* scope; int /*<<< orphan*/  aml_end; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DESC_TYPE_STATE_RPSCOPE ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int /*<<< orphan*/  ACPI_VAR_ARGS ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 union acpi_generic_state* acpi_ut_create_generic_state () ; 
 int /*<<< orphan*/  ps_init_scope ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ps_init_scope(struct acpi_parse_state * parser_state,
		   union acpi_parse_object * root_op)
{
	union acpi_generic_state *scope;

	ACPI_FUNCTION_TRACE_PTR(ps_init_scope, root_op);

	scope = acpi_ut_create_generic_state();
	if (!scope) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	scope->common.descriptor_type = ACPI_DESC_TYPE_STATE_RPSCOPE;
	scope->parse_scope.op = root_op;
	scope->parse_scope.arg_count = ACPI_VAR_ARGS;
	scope->parse_scope.arg_end = parser_state->aml_end;
	scope->parse_scope.pkg_end = parser_state->aml_end;

	parser_state->scope = scope;
	parser_state->start_op = root_op;

	return_ACPI_STATUS(AE_OK);
}