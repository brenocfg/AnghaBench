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
struct acpi_ec {int /*<<< orphan*/  lock; int /*<<< orphan*/  curr; } ;

/* Variables and functions */
 scalar_t__ ACPI_EC_EVT_TIMING_EVENT ; 
 int /*<<< orphan*/  advance_transaction (struct acpi_ec*) ; 
 scalar_t__ ec_event_clearing ; 
 scalar_t__ ec_guard (struct acpi_ec*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void acpi_ec_check_event(struct acpi_ec *ec)
{
	unsigned long flags;

	if (ec_event_clearing == ACPI_EC_EVT_TIMING_EVENT) {
		if (ec_guard(ec)) {
			spin_lock_irqsave(&ec->lock, flags);
			/*
			 * Take care of the SCI_EVT unless no one else is
			 * taking care of it.
			 */
			if (!ec->curr)
				advance_transaction(ec);
			spin_unlock_irqrestore(&ec->lock, flags);
		}
	}
}