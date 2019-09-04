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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 scalar_t__ eeh_enabled () ; 
 int /*<<< orphan*/  eeh_send_failure_event (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pnv_eeh_event(int irq, void *data)
{
	/*
	 * We simply send a special EEH event if EEH has been
	 * enabled. We don't care about EEH events until we've
	 * finished processing the outstanding ones. Event processing
	 * gets unmasked in next_error() if EEH is enabled.
	 */
	disable_irq_nosync(irq);

	if (eeh_enabled())
		eeh_send_failure_event(NULL);

	return IRQ_HANDLED;
}