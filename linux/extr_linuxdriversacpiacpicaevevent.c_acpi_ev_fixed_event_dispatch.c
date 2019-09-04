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
typedef  size_t u32 ;
struct TYPE_4__ {size_t (* handler ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  context; } ;
struct TYPE_3__ {int /*<<< orphan*/  enable_register_id; int /*<<< orphan*/  status_register_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CLEAR_STATUS ; 
 int /*<<< orphan*/  ACPI_DISABLE_EVENT ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 size_t ACPI_INTERRUPT_NOT_HANDLED ; 
 int /*<<< orphan*/  AE_INFO ; 
 TYPE_2__* acpi_gbl_fixed_event_handlers ; 
 TYPE_1__* acpi_gbl_fixed_event_info ; 
 int /*<<< orphan*/  acpi_ut_get_event_name (size_t) ; 
 int /*<<< orphan*/  acpi_write_bit_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 acpi_ev_fixed_event_dispatch(u32 event)
{

	ACPI_FUNCTION_ENTRY();

	/* Clear the status bit */

	(void)acpi_write_bit_register(acpi_gbl_fixed_event_info[event].
				      status_register_id, ACPI_CLEAR_STATUS);

	/*
	 * Make sure that a handler exists. If not, report an error
	 * and disable the event to prevent further interrupts.
	 */
	if (!acpi_gbl_fixed_event_handlers[event].handler) {
		(void)acpi_write_bit_register(acpi_gbl_fixed_event_info[event].
					      enable_register_id,
					      ACPI_DISABLE_EVENT);

		ACPI_ERROR((AE_INFO,
			    "No installed handler for fixed event - %s (%u), disabling",
			    acpi_ut_get_event_name(event), event));

		return (ACPI_INTERRUPT_NOT_HANDLED);
	}

	/* Invoke the Fixed Event handler */

	return ((acpi_gbl_fixed_event_handlers[event].
		 handler) (acpi_gbl_fixed_event_handlers[event].context));
}