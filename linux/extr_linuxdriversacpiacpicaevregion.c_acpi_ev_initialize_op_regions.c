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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 size_t ACPI_NUM_DEFAULT_SPACES ; 
 int /*<<< orphan*/  ACPI_REG_CONNECT ; 
 int /*<<< orphan*/  acpi_ev_execute_reg_methods (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_ev_has_default_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * acpi_gbl_default_address_spaces ; 
 int /*<<< orphan*/  acpi_gbl_root_node ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_initialize_op_regions ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ev_initialize_op_regions(void)
{
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TRACE(ev_initialize_op_regions);

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Run the _REG methods for op_regions in each default address space */

	for (i = 0; i < ACPI_NUM_DEFAULT_SPACES; i++) {
		/*
		 * Make sure the installed handler is the DEFAULT handler. If not the
		 * default, the _REG methods will have already been run (when the
		 * handler was installed)
		 */
		if (acpi_ev_has_default_handler(acpi_gbl_root_node,
						acpi_gbl_default_address_spaces
						[i])) {
			acpi_ev_execute_reg_methods(acpi_gbl_root_node,
						    acpi_gbl_default_address_spaces
						    [i], ACPI_REG_CONNECT);
		}
	}

	(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	return_ACPI_STATUS(status);
}