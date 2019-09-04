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
struct acpi_ec {unsigned long timestamp; int /*<<< orphan*/  wait; scalar_t__ busy_polling; int /*<<< orphan*/  polling_guard; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  acpi_ec_guard_event (struct acpi_ec*) ; 
 scalar_t__ ec_transaction_completed (struct acpi_ec*) ; 
 int /*<<< orphan*/  ec_transaction_polled (struct acpi_ec*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  jiffies_to_usecs (unsigned long) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 unsigned long usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,scalar_t__,unsigned long) ; 

__attribute__((used)) static int ec_guard(struct acpi_ec *ec)
{
	unsigned long guard = usecs_to_jiffies(ec->polling_guard);
	unsigned long timeout = ec->timestamp + guard;

	/* Ensure guarding period before polling EC status */
	do {
		if (ec->busy_polling) {
			/* Perform busy polling */
			if (ec_transaction_completed(ec))
				return 0;
			udelay(jiffies_to_usecs(guard));
		} else {
			/*
			 * Perform wait polling
			 * 1. Wait the transaction to be completed by the
			 *    GPE handler after the transaction enters
			 *    ACPI_EC_COMMAND_POLL state.
			 * 2. A special guarding logic is also required
			 *    for event clearing mode "event" before the
			 *    transaction enters ACPI_EC_COMMAND_POLL
			 *    state.
			 */
			if (!ec_transaction_polled(ec) &&
			    !acpi_ec_guard_event(ec))
				break;
			if (wait_event_timeout(ec->wait,
					       ec_transaction_completed(ec),
					       guard))
				return 0;
		}
	} while (time_before(jiffies, timeout));
	return -ETIME;
}