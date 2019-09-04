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
typedef  void* uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* irqhook ) (int,void*,void*,void*) ;scalar_t__ semaphore; } ;
struct TYPE_5__ {int* seq; size_t idx; size_t actidx; TYPE_1__ act; } ;
typedef  TYPE_2__ hp_sdc_transaction ;
struct TYPE_6__ {size_t rcurr; scalar_t__ rqty; int /*<<< orphan*/  task; int /*<<< orphan*/  rtq_lock; int /*<<< orphan*/  rtime; TYPE_2__** tq; } ;

/* Variables and functions */
 int HP_SDC_ACT_CALLBACK ; 
 int HP_SDC_ACT_SEMAPHORE ; 
 TYPE_3__ hp_sdc ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,void*,void*,void*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (scalar_t__) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hp_sdc_take(int irq, void *dev_id, uint8_t status, uint8_t data)
{
	hp_sdc_transaction *curr;

	read_lock(&hp_sdc.rtq_lock);
	if (hp_sdc.rcurr < 0) {
		read_unlock(&hp_sdc.rtq_lock);
		return;
	}
	curr = hp_sdc.tq[hp_sdc.rcurr];
	read_unlock(&hp_sdc.rtq_lock);

	curr->seq[curr->idx++] = status;
	curr->seq[curr->idx++] = data;
	hp_sdc.rqty -= 2;
	hp_sdc.rtime = ktime_get();

	if (hp_sdc.rqty <= 0) {
		/* All data has been gathered. */
		if (curr->seq[curr->actidx] & HP_SDC_ACT_SEMAPHORE)
			if (curr->act.semaphore)
				up(curr->act.semaphore);

		if (curr->seq[curr->actidx] & HP_SDC_ACT_CALLBACK)
			if (curr->act.irqhook)
				curr->act.irqhook(irq, dev_id, status, data);

		curr->actidx = curr->idx;
		curr->idx++;
		/* Return control of this transaction */
		write_lock(&hp_sdc.rtq_lock);
		hp_sdc.rcurr = -1;
		hp_sdc.rqty = 0;
		write_unlock(&hp_sdc.rtq_lock);
		tasklet_schedule(&hp_sdc.task);
	}
}