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
struct acpi_ec {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_FLAGS_STARTED ; 
 int /*<<< orphan*/  EC_FLAGS_STOPPED ; 
 int /*<<< orphan*/  __acpi_ec_disable_event (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_complete_request (struct acpi_ec*) ; 
 scalar_t__ acpi_ec_started (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_stopped (struct acpi_ec*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ec_dbg_drv (char*) ; 
 int /*<<< orphan*/  ec_dbg_ref (struct acpi_ec*,char*) ; 
 int /*<<< orphan*/  ec_freeze_events ; 
 int /*<<< orphan*/  ec_log_drv (char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_ec_stop(struct acpi_ec *ec, bool suspending)
{
	unsigned long flags;

	spin_lock_irqsave(&ec->lock, flags);
	if (acpi_ec_started(ec)) {
		ec_dbg_drv("Stopping EC");
		set_bit(EC_FLAGS_STOPPED, &ec->flags);
		spin_unlock_irqrestore(&ec->lock, flags);
		wait_event(ec->wait, acpi_ec_stopped(ec));
		spin_lock_irqsave(&ec->lock, flags);
		/* Disable GPE for event processing (SCI_EVT=1) */
		if (!suspending) {
			acpi_ec_complete_request(ec);
			ec_dbg_ref(ec, "Decrease driver");
		} else if (!ec_freeze_events)
			__acpi_ec_disable_event(ec);
		clear_bit(EC_FLAGS_STARTED, &ec->flags);
		clear_bit(EC_FLAGS_STOPPED, &ec->flags);
		ec_log_drv("EC stopped");
	}
	spin_unlock_irqrestore(&ec->lock, flags);
}