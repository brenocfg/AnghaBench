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
struct enic {int /*<<< orphan*/  reset; int /*<<< orphan*/ * intr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ enic_log_q_error (struct enic*) ; 
 unsigned int enic_msix_err_intr (struct enic*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_return_all_credits (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t enic_isr_msix_err(int irq, void *data)
{
	struct enic *enic = data;
	unsigned int intr = enic_msix_err_intr(enic);

	vnic_intr_return_all_credits(&enic->intr[intr]);

	if (enic_log_q_error(enic))
		/* schedule recovery from WQ/RQ error */
		schedule_work(&enic->reset);

	return IRQ_HANDLED;
}