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
struct transaction {scalar_t__ irq_count; int /*<<< orphan*/  command; } ;
struct acpi_ec {int /*<<< orphan*/  lock; struct transaction* curr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  acpi_ec_cmd_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ec_complete_request (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_submit_flushable_request (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_unmask_gpe (struct acpi_ec*) ; 
 int /*<<< orphan*/  ec_dbg_ref (struct acpi_ec*,char*) ; 
 int /*<<< orphan*/  ec_dbg_req (char*,int /*<<< orphan*/ ) ; 
 int ec_poll (struct acpi_ec*) ; 
 scalar_t__ ec_storm_threshold ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_transaction (struct acpi_ec*) ; 

__attribute__((used)) static int acpi_ec_transaction_unlocked(struct acpi_ec *ec,
					struct transaction *t)
{
	unsigned long tmp;
	int ret = 0;

	/* start transaction */
	spin_lock_irqsave(&ec->lock, tmp);
	/* Enable GPE for command processing (IBF=0/OBF=1) */
	if (!acpi_ec_submit_flushable_request(ec)) {
		ret = -EINVAL;
		goto unlock;
	}
	ec_dbg_ref(ec, "Increase command");
	/* following two actions should be kept atomic */
	ec->curr = t;
	ec_dbg_req("Command(%s) started", acpi_ec_cmd_string(t->command));
	start_transaction(ec);
	spin_unlock_irqrestore(&ec->lock, tmp);

	ret = ec_poll(ec);

	spin_lock_irqsave(&ec->lock, tmp);
	if (t->irq_count == ec_storm_threshold)
		acpi_ec_unmask_gpe(ec);
	ec_dbg_req("Command(%s) stopped", acpi_ec_cmd_string(t->command));
	ec->curr = NULL;
	/* Disable GPE for command processing (IBF=0/OBF=1) */
	acpi_ec_complete_request(ec);
	ec_dbg_ref(ec, "Decrease command");
unlock:
	spin_unlock_irqrestore(&ec->lock, tmp);
	return ret;
}