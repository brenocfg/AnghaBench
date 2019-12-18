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
struct isci_host {TYPE_1__* smu_registers; } ;
struct TYPE_2__ {int /*<<< orphan*/  interrupt_mask; int /*<<< orphan*/  interrupt_status; } ;

/* Variables and functions */
 int SMU_ISR_COMPLETION ; 
 scalar_t__ sci_controller_completion_queue_has_entries (struct isci_host*) ; 
 int /*<<< orphan*/  sci_controller_process_completions (struct isci_host*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sci_controller_completion_handler(struct isci_host *ihost)
{
	/* Empty out the completion queue */
	if (sci_controller_completion_queue_has_entries(ihost))
		sci_controller_process_completions(ihost);

	/* Clear the interrupt and enable all interrupts again */
	writel(SMU_ISR_COMPLETION, &ihost->smu_registers->interrupt_status);
	/* Could we write the value of SMU_ISR_COMPLETION? */
	writel(0xFF000000, &ihost->smu_registers->interrupt_mask);
	writel(0, &ihost->smu_registers->interrupt_mask);
}