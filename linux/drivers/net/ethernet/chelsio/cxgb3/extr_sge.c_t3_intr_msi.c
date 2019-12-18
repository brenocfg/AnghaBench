#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sge_rspq {int /*<<< orphan*/  lock; int /*<<< orphan*/  unhandled_irqs; int /*<<< orphan*/  cidx; int /*<<< orphan*/  next_holdoff; int /*<<< orphan*/  cntxt_id; } ;
struct TYPE_5__ {TYPE_3__* qs; } ;
struct TYPE_4__ {int nports; } ;
struct adapter {TYPE_2__ sge; TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {struct sge_rspq rspq; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_GTS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int V_NEWINDEX (int /*<<< orphan*/ ) ; 
 int V_NEWTIMER (int /*<<< orphan*/ ) ; 
 int V_RSPQ (int /*<<< orphan*/ ) ; 
 scalar_t__ process_responses (struct adapter*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ t3_slow_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t t3_intr_msi(int irq, void *cookie)
{
	int new_packets = 0;
	struct adapter *adap = cookie;
	struct sge_rspq *q = &adap->sge.qs[0].rspq;

	spin_lock(&q->lock);

	if (process_responses(adap, &adap->sge.qs[0], -1)) {
		t3_write_reg(adap, A_SG_GTS, V_RSPQ(q->cntxt_id) |
			     V_NEWTIMER(q->next_holdoff) | V_NEWINDEX(q->cidx));
		new_packets = 1;
	}

	if (adap->params.nports == 2 &&
	    process_responses(adap, &adap->sge.qs[1], -1)) {
		struct sge_rspq *q1 = &adap->sge.qs[1].rspq;

		t3_write_reg(adap, A_SG_GTS, V_RSPQ(q1->cntxt_id) |
			     V_NEWTIMER(q1->next_holdoff) |
			     V_NEWINDEX(q1->cidx));
		new_packets = 1;
	}

	if (!new_packets && t3_slow_intr_handler(adap) == 0)
		q->unhandled_irqs++;

	spin_unlock(&q->lock);
	return IRQ_HANDLED;
}