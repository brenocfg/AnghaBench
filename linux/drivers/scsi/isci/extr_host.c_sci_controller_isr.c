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
struct isci_host {int /*<<< orphan*/  scic_lock; TYPE_1__* smu_registers; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  interrupt_mask; int /*<<< orphan*/  interrupt_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IHOST_IRQ_ENABLED ; 
 int SMU_ISR_COMPLETION ; 
 scalar_t__ sci_controller_completion_queue_has_entries (struct isci_host*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool sci_controller_isr(struct isci_host *ihost)
{
	if (sci_controller_completion_queue_has_entries(ihost))
		return true;

	/* we have a spurious interrupt it could be that we have already
	 * emptied the completion queue from a previous interrupt
	 * FIXME: really!?
	 */
	writel(SMU_ISR_COMPLETION, &ihost->smu_registers->interrupt_status);

	/* There is a race in the hardware that could cause us not to be
	 * notified of an interrupt completion if we do not take this
	 * step.  We will mask then unmask the interrupts so if there is
	 * another interrupt pending the clearing of the interrupt
	 * source we get the next interrupt message.
	 */
	spin_lock(&ihost->scic_lock);
	if (test_bit(IHOST_IRQ_ENABLED, &ihost->flags)) {
		writel(0xFF000000, &ihost->smu_registers->interrupt_mask);
		writel(0, &ihost->smu_registers->interrupt_mask);
	}
	spin_unlock(&ihost->scic_lock);

	return false;
}