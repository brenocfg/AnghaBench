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
struct enic {int /*<<< orphan*/ * intr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int enic_msix_notify_intr (struct enic*) ; 
 int /*<<< orphan*/  enic_notify_check (struct enic*) ; 
 int /*<<< orphan*/  vnic_intr_return_all_credits (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t enic_isr_msix_notify(int irq, void *data)
{
	struct enic *enic = data;
	unsigned int intr = enic_msix_notify_intr(enic);

	enic_notify_check(enic);
	vnic_intr_return_all_credits(&enic->intr[intr]);

	return IRQ_HANDLED;
}