#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  unhandled_irqs; } ;
struct TYPE_3__ {int /*<<< orphan*/  cidx; } ;
struct sge {TYPE_2__ stats; TYPE_1__ respQ; } ;
struct adapter {int /*<<< orphan*/  async_lock; int /*<<< orphan*/  napi; scalar_t__ regs; struct sge* sge; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ A_PL_CAUSE ; 
 scalar_t__ A_SG_SLEEPING ; 
 int /*<<< orphan*/  F_PL_INTR_SGE_DATA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 scalar_t__ process_pure_responses (struct adapter*) ; 
 int /*<<< orphan*/  responses_pending (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int t1_slow_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

irqreturn_t t1_interrupt(int irq, void *data)
{
	struct adapter *adapter = data;
	struct sge *sge = adapter->sge;
	int handled;

	if (likely(responses_pending(adapter))) {
		writel(F_PL_INTR_SGE_DATA, adapter->regs + A_PL_CAUSE);

		if (napi_schedule_prep(&adapter->napi)) {
			if (process_pure_responses(adapter))
				__napi_schedule(&adapter->napi);
			else {
				/* no data, no NAPI needed */
				writel(sge->respQ.cidx, adapter->regs + A_SG_SLEEPING);
				/* undo schedule_prep */
				napi_enable(&adapter->napi);
			}
		}
		return IRQ_HANDLED;
	}

	spin_lock(&adapter->async_lock);
	handled = t1_slow_intr_handler(adapter);
	spin_unlock(&adapter->async_lock);

	if (!handled)
		sge->stats.unhandled_irqs++;

	return IRQ_RETVAL(handled != 0);
}