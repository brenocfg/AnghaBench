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
struct nicvf_cq_poll {int cq_idx; int /*<<< orphan*/  napi; struct nicvf* nicvf; } ;
struct nicvf {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  NICVF_INTR_CQ ; 
 int /*<<< orphan*/  napi_schedule_irqoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nicvf_clear_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_disable_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_dump_intr_status (struct nicvf*) ; 

__attribute__((used)) static irqreturn_t nicvf_intr_handler(int irq, void *cq_irq)
{
	struct nicvf_cq_poll *cq_poll = (struct nicvf_cq_poll *)cq_irq;
	struct nicvf *nic = cq_poll->nicvf;
	int qidx = cq_poll->cq_idx;

	nicvf_dump_intr_status(nic);

	/* Disable interrupts */
	nicvf_disable_intr(nic, NICVF_INTR_CQ, qidx);

	/* Schedule NAPI */
	napi_schedule_irqoff(&cq_poll->napi);

	/* Clear interrupt */
	nicvf_clear_intr(nic, NICVF_INTR_CQ, qidx);

	return IRQ_HANDLED;
}