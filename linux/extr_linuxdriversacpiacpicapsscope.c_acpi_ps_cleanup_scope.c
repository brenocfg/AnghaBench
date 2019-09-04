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
typedef  union acpi_generic_state {int dummy; } acpi_generic_state ;
struct acpi_parse_state {scalar_t__ scope; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_parse_state*) ; 
 int /*<<< orphan*/  acpi_ut_delete_generic_state (union acpi_generic_state*) ; 
 union acpi_generic_state* acpi_ut_pop_generic_state (scalar_t__*) ; 
 int /*<<< orphan*/  ps_cleanup_scope ; 
 int /*<<< orphan*/  return_VOID ; 

void acpi_ps_cleanup_scope(struct acpi_parse_state *parser_state)
{
	union acpi_generic_state *scope;

	ACPI_FUNCTION_TRACE_PTR(ps_cleanup_scope, parser_state);

	if (!parser_state) {
		return_VOID;
	}

	/* Delete anything on the scope stack */

	while (parser_state->scope) {
		scope = acpi_ut_pop_generic_state(&parser_state->scope);
		acpi_ut_delete_generic_state(scope);
	}

	return_VOID;
}