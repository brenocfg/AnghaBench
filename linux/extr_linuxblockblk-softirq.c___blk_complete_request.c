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
struct request_queue {int /*<<< orphan*/  queue_flags; int /*<<< orphan*/  softirq_done_fn; } ;
struct request {int cpu; int /*<<< orphan*/  ipi_list; struct request_queue* q; } ;
struct list_head {int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_SOFTIRQ ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  QUEUE_FLAG_SAME_FORCE ; 
 int /*<<< orphan*/  blk_cpu_done ; 
 int cpus_share_cache (int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ raise_blk_irq (int,struct request*) ; 
 int /*<<< orphan*/  raise_softirq_irqoff (int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct list_head* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void __blk_complete_request(struct request *req)
{
	int ccpu, cpu;
	struct request_queue *q = req->q;
	unsigned long flags;
	bool shared = false;

	BUG_ON(!q->softirq_done_fn);

	local_irq_save(flags);
	cpu = smp_processor_id();

	/*
	 * Select completion CPU
	 */
	if (req->cpu != -1) {
		ccpu = req->cpu;
		if (!test_bit(QUEUE_FLAG_SAME_FORCE, &q->queue_flags))
			shared = cpus_share_cache(cpu, ccpu);
	} else
		ccpu = cpu;

	/*
	 * If current CPU and requested CPU share a cache, run the softirq on
	 * the current CPU. One might concern this is just like
	 * QUEUE_FLAG_SAME_FORCE, but actually not. blk_complete_request() is
	 * running in interrupt handler, and currently I/O controller doesn't
	 * support multiple interrupts, so current CPU is unique actually. This
	 * avoids IPI sending from current CPU to the first CPU of a group.
	 */
	if (ccpu == cpu || shared) {
		struct list_head *list;
do_local:
		list = this_cpu_ptr(&blk_cpu_done);
		list_add_tail(&req->ipi_list, list);

		/*
		 * if the list only contains our just added request,
		 * signal a raise of the softirq. If there are already
		 * entries there, someone already raised the irq but it
		 * hasn't run yet.
		 */
		if (list->next == &req->ipi_list)
			raise_softirq_irqoff(BLOCK_SOFTIRQ);
	} else if (raise_blk_irq(ccpu, req))
		goto do_local;

	local_irq_restore(flags);
}