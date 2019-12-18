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
typedef  int u32 ;
struct sge_rspq {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {TYPE_2__* qs; } ;
struct adapter {TYPE_1__ sge; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {struct sge_rspq rspq; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PL_CLI ; 
 int /*<<< orphan*/  A_SG_DATA_INTR ; 
 int F_ERRINTR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  process_responses_gts (struct adapter*,struct sge_rspq*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_slow_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t t3b_intr(int irq, void *cookie)
{
	u32 map;
	struct adapter *adap = cookie;
	struct sge_rspq *q0 = &adap->sge.qs[0].rspq;

	t3_write_reg(adap, A_PL_CLI, 0);
	map = t3_read_reg(adap, A_SG_DATA_INTR);

	if (unlikely(!map))	/* shared interrupt, most likely */
		return IRQ_NONE;

	spin_lock(&q0->lock);

	if (unlikely(map & F_ERRINTR))
		t3_slow_intr_handler(adap);

	if (likely(map & 1))
		process_responses_gts(adap, q0);

	if (map & 2)
		process_responses_gts(adap, &adap->sge.qs[1].rspq);

	spin_unlock(&q0->lock);
	return IRQ_HANDLED;
}