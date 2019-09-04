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
struct acpi_ec {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_FLAGS_STARTED ; 
 int /*<<< orphan*/  acpi_ec_submit_request (struct acpi_ec*) ; 
 int /*<<< orphan*/  ec_dbg_drv (char*) ; 
 int /*<<< orphan*/  ec_dbg_ref (struct acpi_ec*,char*) ; 
 int /*<<< orphan*/  ec_log_drv (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_ec_start(struct acpi_ec *ec, bool resuming)
{
	unsigned long flags;

	spin_lock_irqsave(&ec->lock, flags);
	if (!test_and_set_bit(EC_FLAGS_STARTED, &ec->flags)) {
		ec_dbg_drv("Starting EC");
		/* Enable GPE for event processing (SCI_EVT=1) */
		if (!resuming) {
			acpi_ec_submit_request(ec);
			ec_dbg_ref(ec, "Increase driver");
		}
		ec_log_drv("EC started");
	}
	spin_unlock_irqrestore(&ec->lock, flags);
}