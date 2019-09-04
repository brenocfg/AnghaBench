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
struct task_struct {int /*<<< orphan*/  pid; } ;
struct cfq_queue {int /*<<< orphan*/  ref; int /*<<< orphan*/  ioprio_class; } ;
struct cfq_io_cq {int /*<<< orphan*/  ioprio; } ;
struct cfq_group {int dummy; } ;
struct cfq_data {struct cfq_queue oom_cfqq; TYPE_1__* queue; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int GFP_NOWAIT ; 
 int /*<<< orphan*/  IOPRIO_CLASS_NONE ; 
 int IOPRIO_PRIO_CLASS (int /*<<< orphan*/ ) ; 
 int IOPRIO_PRIO_DATA (int /*<<< orphan*/ ) ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  bio_blkcg (struct bio*) ; 
 struct cfq_queue** cfq_async_queue_prio (struct cfq_group*,int,int) ; 
 int /*<<< orphan*/  cfq_init_cfqq (struct cfq_data*,struct cfq_queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cfq_init_prio_data (struct cfq_queue*,struct cfq_io_cq*) ; 
 int /*<<< orphan*/  cfq_link_cfqq_cfqg (struct cfq_queue*,struct cfq_group*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*) ; 
 struct cfq_group* cfq_lookup_cfqg (struct cfq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_pool ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  ioprio_valid (int /*<<< orphan*/ ) ; 
 struct cfq_queue* kmem_cache_alloc_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int task_nice_ioclass (struct task_struct*) ; 
 int task_nice_ioprio (struct task_struct*) ; 

__attribute__((used)) static struct cfq_queue *
cfq_get_queue(struct cfq_data *cfqd, bool is_sync, struct cfq_io_cq *cic,
	      struct bio *bio)
{
	int ioprio_class = IOPRIO_PRIO_CLASS(cic->ioprio);
	int ioprio = IOPRIO_PRIO_DATA(cic->ioprio);
	struct cfq_queue **async_cfqq = NULL;
	struct cfq_queue *cfqq;
	struct cfq_group *cfqg;

	rcu_read_lock();
	cfqg = cfq_lookup_cfqg(cfqd, bio_blkcg(bio));
	if (!cfqg) {
		cfqq = &cfqd->oom_cfqq;
		goto out;
	}

	if (!is_sync) {
		if (!ioprio_valid(cic->ioprio)) {
			struct task_struct *tsk = current;
			ioprio = task_nice_ioprio(tsk);
			ioprio_class = task_nice_ioclass(tsk);
		}
		async_cfqq = cfq_async_queue_prio(cfqg, ioprio_class, ioprio);
		cfqq = *async_cfqq;
		if (cfqq)
			goto out;
	}

	cfqq = kmem_cache_alloc_node(cfq_pool,
				     GFP_NOWAIT | __GFP_ZERO | __GFP_NOWARN,
				     cfqd->queue->node);
	if (!cfqq) {
		cfqq = &cfqd->oom_cfqq;
		goto out;
	}

	/* cfq_init_cfqq() assumes cfqq->ioprio_class is initialized. */
	cfqq->ioprio_class = IOPRIO_CLASS_NONE;
	cfq_init_cfqq(cfqd, cfqq, current->pid, is_sync);
	cfq_init_prio_data(cfqq, cic);
	cfq_link_cfqq_cfqg(cfqq, cfqg);
	cfq_log_cfqq(cfqd, cfqq, "alloced");

	if (async_cfqq) {
		/* a new async queue is created, pin and remember */
		cfqq->ref++;
		*async_cfqq = cfqq;
	}
out:
	cfqq->ref++;
	rcu_read_unlock();
	return cfqq;
}