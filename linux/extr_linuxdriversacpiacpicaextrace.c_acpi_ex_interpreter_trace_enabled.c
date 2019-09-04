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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int ACPI_TRACE_ENABLED ; 
 int ACPI_TRACE_ONESHOT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int acpi_gbl_trace_flags ; 
 scalar_t__ acpi_gbl_trace_method_name ; 
 scalar_t__ acpi_gbl_trace_method_object ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static u8 acpi_ex_interpreter_trace_enabled(char *name)
{

	/* Check if tracing is enabled */

	if (!(acpi_gbl_trace_flags & ACPI_TRACE_ENABLED)) {
		return (FALSE);
	}

	/*
	 * Check if tracing is filtered:
	 *
	 * 1. If the tracer is started, acpi_gbl_trace_method_object should have
	 *    been filled by the trace starter
	 * 2. If the tracer is not started, acpi_gbl_trace_method_name should be
	 *    matched if it is specified
	 * 3. If the tracer is oneshot style, acpi_gbl_trace_method_name should
	 *    not be cleared by the trace stopper during the first match
	 */
	if (acpi_gbl_trace_method_object) {
		return (TRUE);
	}

	if (name &&
	    (acpi_gbl_trace_method_name &&
	     strcmp(acpi_gbl_trace_method_name, name))) {
		return (FALSE);
	}

	if ((acpi_gbl_trace_flags & ACPI_TRACE_ONESHOT) &&
	    !acpi_gbl_trace_method_name) {
		return (FALSE);
	}

	return (TRUE);
}