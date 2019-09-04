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
struct sge_rspq {int /*<<< orphan*/  lock; int /*<<< orphan*/  cidx; int /*<<< orphan*/  next_holdoff; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  unhandled_irqs; } ;
struct sge_qset {struct sge_rspq rspq; struct adapter* adap; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_GTS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int V_NEWINDEX (int /*<<< orphan*/ ) ; 
 int V_NEWTIMER (int /*<<< orphan*/ ) ; 
 int V_RSPQ (int /*<<< orphan*/ ) ; 
 scalar_t__ process_responses (struct adapter*,struct sge_qset*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t t3_sge_intr_msix(int irq, void *cookie)
{
	struct sge_qset *qs = cookie;
	struct adapter *adap = qs->adap;
	struct sge_rspq *q = &qs->rspq;

	spin_lock(&q->lock);
	if (process_responses(adap, qs, -1) == 0)
		q->unhandled_irqs++;
	t3_write_reg(adap, A_SG_GTS, V_RSPQ(q->cntxt_id) |
		     V_NEWTIMER(q->next_holdoff) | V_NEWINDEX(q->cidx));
	spin_unlock(&q->lock);
	return IRQ_HANDLED;
}