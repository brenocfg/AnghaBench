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
typedef  int u32 ;
struct isci_host {TYPE_1__* smu_registers; } ;
struct TYPE_2__ {int /*<<< orphan*/  interrupt_mask; int /*<<< orphan*/  interrupt_status; } ;

/* Variables and functions */
 int SMU_ISR_QUEUE_ERROR ; 
 int SMU_ISR_QUEUE_SUSPEND ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool sci_controller_error_isr(struct isci_host *ihost)
{
	u32 interrupt_status;

	interrupt_status =
		readl(&ihost->smu_registers->interrupt_status);
	interrupt_status &= (SMU_ISR_QUEUE_ERROR | SMU_ISR_QUEUE_SUSPEND);

	if (interrupt_status != 0) {
		/*
		 * There is an error interrupt pending so let it through and handle
		 * in the callback */
		return true;
	}

	/*
	 * There is a race in the hardware that could cause us not to be notified
	 * of an interrupt completion if we do not take this step.  We will mask
	 * then unmask the error interrupts so if there was another interrupt
	 * pending we will be notified.
	 * Could we write the value of (SMU_ISR_QUEUE_ERROR | SMU_ISR_QUEUE_SUSPEND)? */
	writel(0xff, &ihost->smu_registers->interrupt_mask);
	writel(0, &ihost->smu_registers->interrupt_mask);

	return false;
}