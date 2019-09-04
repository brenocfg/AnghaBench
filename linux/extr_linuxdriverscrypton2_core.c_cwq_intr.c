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
struct spu_queue {unsigned long head; int /*<<< orphan*/  lock; int /*<<< orphan*/  qhandle; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned long HV_EOK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned long,...) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned long spu_next_offset (struct spu_queue*,unsigned long) ; 
 unsigned long sun4v_ncs_gethead (int /*<<< orphan*/ ,unsigned long*) ; 
 unsigned long sun4v_ncs_sethead_marker (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static irqreturn_t cwq_intr(int irq, void *dev_id)
{
	unsigned long off, new_head, hv_ret;
	struct spu_queue *q = dev_id;

	pr_err("CPU[%d]: Got CWQ interrupt for qhdl[%lx]\n",
	       smp_processor_id(), q->qhandle);

	spin_lock(&q->lock);

	hv_ret = sun4v_ncs_gethead(q->qhandle, &new_head);

	pr_err("CPU[%d]: CWQ gethead[%lx] hv_ret[%lu]\n",
	       smp_processor_id(), new_head, hv_ret);

	for (off = q->head; off != new_head; off = spu_next_offset(q, off)) {
		/* XXX ... XXX */
	}

	hv_ret = sun4v_ncs_sethead_marker(q->qhandle, new_head);
	if (hv_ret == HV_EOK)
		q->head = new_head;

	spin_unlock(&q->lock);

	return IRQ_HANDLED;
}