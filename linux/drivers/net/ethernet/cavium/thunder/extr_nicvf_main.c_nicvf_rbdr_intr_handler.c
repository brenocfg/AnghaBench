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
typedef  scalar_t__ u8 ;
struct nicvf {int /*<<< orphan*/  rbdr_task; TYPE_1__* qs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ rbdr_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  NICVF_INTR_RBDR ; 
 int /*<<< orphan*/  nicvf_clear_intr (struct nicvf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nicvf_disable_intr (struct nicvf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nicvf_dump_intr_status (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_is_intr_enabled (struct nicvf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t nicvf_rbdr_intr_handler(int irq, void *nicvf_irq)
{
	struct nicvf *nic = (struct nicvf *)nicvf_irq;
	u8 qidx;


	nicvf_dump_intr_status(nic);

	/* Disable RBDR interrupt and schedule softirq */
	for (qidx = 0; qidx < nic->qs->rbdr_cnt; qidx++) {
		if (!nicvf_is_intr_enabled(nic, NICVF_INTR_RBDR, qidx))
			continue;
		nicvf_disable_intr(nic, NICVF_INTR_RBDR, qidx);
		tasklet_hi_schedule(&nic->rbdr_task);
		/* Clear interrupt */
		nicvf_clear_intr(nic, NICVF_INTR_RBDR, qidx);
	}

	return IRQ_HANDLED;
}