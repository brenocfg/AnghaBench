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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  acpi_trace_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_TRACE_POINT ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_get_trace_event_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_trace_point ; 

void
acpi_ex_trace_point(acpi_trace_event_type type,
		    u8 begin, u8 *aml, char *pathname)
{

	ACPI_FUNCTION_NAME(ex_trace_point);

	if (pathname) {
		ACPI_DEBUG_PRINT((ACPI_DB_TRACE_POINT,
				  "%s %s [0x%p:%s] execution.\n",
				  acpi_ex_get_trace_event_name(type),
				  begin ? "Begin" : "End", aml, pathname));
	} else {
		ACPI_DEBUG_PRINT((ACPI_DB_TRACE_POINT,
				  "%s %s [0x%p] execution.\n",
				  acpi_ex_get_trace_event_name(type),
				  begin ? "Begin" : "End", aml));
	}
}