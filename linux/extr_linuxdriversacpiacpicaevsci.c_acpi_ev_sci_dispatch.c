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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_sci_handler_info {struct acpi_sci_handler_info* next; int /*<<< orphan*/  context; int /*<<< orphan*/  (* address ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  acpi_cpu_flags ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_INTERRUPT_NOT_HANDLED ; 
 int /*<<< orphan*/  acpi_gbl_gpe_lock ; 
 struct acpi_sci_handler_info* acpi_gbl_sci_handler_list ; 
 int /*<<< orphan*/  acpi_os_acquire_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_release_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_sci_dispatch ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

u32 acpi_ev_sci_dispatch(void)
{
	struct acpi_sci_handler_info *sci_handler;
	acpi_cpu_flags flags;
	u32 int_status = ACPI_INTERRUPT_NOT_HANDLED;

	ACPI_FUNCTION_NAME(ev_sci_dispatch);

	/* Are there any host-installed SCI handlers? */

	if (!acpi_gbl_sci_handler_list) {
		return (int_status);
	}

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Invoke all host-installed SCI handlers */

	sci_handler = acpi_gbl_sci_handler_list;
	while (sci_handler) {

		/* Invoke the installed handler (at interrupt level) */

		int_status |= sci_handler->address(sci_handler->context);

		sci_handler = sci_handler->next;
	}

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	return (int_status);
}