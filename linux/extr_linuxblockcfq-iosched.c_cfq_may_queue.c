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
struct task_struct {int /*<<< orphan*/  io_context; } ;
struct request_queue {TYPE_1__* elevator; } ;
struct cfq_queue {int dummy; } ;
struct cfq_io_cq {int dummy; } ;
struct cfq_data {int dummy; } ;
struct TYPE_2__ {struct cfq_data* elevator_data; } ;

/* Variables and functions */
 int ELV_MQUEUE_MAY ; 
 int __cfq_may_queue (struct cfq_queue*) ; 
 struct cfq_io_cq* cfq_cic_lookup (struct cfq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_init_prio_data (struct cfq_queue*,struct cfq_io_cq*) ; 
 int /*<<< orphan*/  cfqq_boost_on_prio (struct cfq_queue*,unsigned int) ; 
 struct cfq_queue* cic_to_cfqq (struct cfq_io_cq*,int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  op_is_sync (unsigned int) ; 

__attribute__((used)) static int cfq_may_queue(struct request_queue *q, unsigned int op)
{
	struct cfq_data *cfqd = q->elevator->elevator_data;
	struct task_struct *tsk = current;
	struct cfq_io_cq *cic;
	struct cfq_queue *cfqq;

	/*
	 * don't force setup of a queue from here, as a call to may_queue
	 * does not necessarily imply that a request actually will be queued.
	 * so just lookup a possibly existing queue, or return 'may queue'
	 * if that fails
	 */
	cic = cfq_cic_lookup(cfqd, tsk->io_context);
	if (!cic)
		return ELV_MQUEUE_MAY;

	cfqq = cic_to_cfqq(cic, op_is_sync(op));
	if (cfqq) {
		cfq_init_prio_data(cfqq, cic);
		cfqq_boost_on_prio(cfqq, op);

		return __cfq_may_queue(cfqq);
	}

	return ELV_MQUEUE_MAY;
}