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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_REGION_DEACTIVATE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ev_default_region_setup ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ev_default_region_setup(acpi_handle handle,
			     u32 function,
			     void *handler_context, void **region_context)
{
	ACPI_FUNCTION_TRACE(ev_default_region_setup);

	if (function == ACPI_REGION_DEACTIVATE) {
		*region_context = NULL;
	} else {
		*region_context = handler_context;
	}

	return_ACPI_STATUS(AE_OK);
}