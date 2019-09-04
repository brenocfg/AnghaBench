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
struct acpi_ec {int /*<<< orphan*/  flags; TYPE_1__* curr; } ;
struct TYPE_2__ {unsigned long flags; scalar_t__ command; } ;

/* Variables and functions */
 unsigned long ACPI_EC_COMMAND_COMPLETE ; 
 unsigned long ACPI_EC_COMMAND_POLL ; 
 scalar_t__ ACPI_EC_COMMAND_QUERY ; 
 scalar_t__ ACPI_EC_EVT_TIMING_EVENT ; 
 scalar_t__ ACPI_EC_EVT_TIMING_QUERY ; 
 scalar_t__ ACPI_EC_EVT_TIMING_STATUS ; 
 int /*<<< orphan*/  EC_FLAGS_QUERY_GUARDING ; 
 int /*<<< orphan*/  acpi_ec_complete_query (struct acpi_ec*) ; 
 scalar_t__ ec_event_clearing ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ec_transaction_transition(struct acpi_ec *ec, unsigned long flag)
{
	ec->curr->flags |= flag;
	if (ec->curr->command == ACPI_EC_COMMAND_QUERY) {
		if (ec_event_clearing == ACPI_EC_EVT_TIMING_STATUS &&
		    flag == ACPI_EC_COMMAND_POLL)
			acpi_ec_complete_query(ec);
		if (ec_event_clearing == ACPI_EC_EVT_TIMING_QUERY &&
		    flag == ACPI_EC_COMMAND_COMPLETE)
			acpi_ec_complete_query(ec);
		if (ec_event_clearing == ACPI_EC_EVT_TIMING_EVENT &&
		    flag == ACPI_EC_COMMAND_COMPLETE)
			set_bit(EC_FLAGS_QUERY_GUARDING, &ec->flags);
	}
}