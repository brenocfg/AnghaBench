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
struct acpi_ec {int /*<<< orphan*/  lock; TYPE_1__* curr; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {scalar_t__ command; } ;

/* Variables and functions */
 scalar_t__ ACPI_EC_COMMAND_QUERY ; 
 scalar_t__ ACPI_EC_EVT_TIMING_QUERY ; 
 scalar_t__ ACPI_EC_EVT_TIMING_STATUS ; 
 int /*<<< orphan*/  EC_FLAGS_QUERY_PENDING ; 
 scalar_t__ ec_event_clearing ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool acpi_ec_guard_event(struct acpi_ec *ec)
{
	bool guarded = true;
	unsigned long flags;

	spin_lock_irqsave(&ec->lock, flags);
	/*
	 * If firmware SCI_EVT clearing timing is "event", we actually
	 * don't know when the SCI_EVT will be cleared by firmware after
	 * evaluating _Qxx, so we need to re-check SCI_EVT after waiting an
	 * acceptable period.
	 *
	 * The guarding period begins when EC_FLAGS_QUERY_PENDING is
	 * flagged, which means SCI_EVT check has just been performed.
	 * But if the current transaction is ACPI_EC_COMMAND_QUERY, the
	 * guarding should have already been performed (via
	 * EC_FLAGS_QUERY_GUARDING) and should not be applied so that the
	 * ACPI_EC_COMMAND_QUERY transaction can be transitioned into
	 * ACPI_EC_COMMAND_POLL state immediately.
	 */
	if (ec_event_clearing == ACPI_EC_EVT_TIMING_STATUS ||
	    ec_event_clearing == ACPI_EC_EVT_TIMING_QUERY ||
	    !test_bit(EC_FLAGS_QUERY_PENDING, &ec->flags) ||
	    (ec->curr && ec->curr->command == ACPI_EC_COMMAND_QUERY))
		guarded = false;
	spin_unlock_irqrestore(&ec->lock, flags);
	return guarded;
}