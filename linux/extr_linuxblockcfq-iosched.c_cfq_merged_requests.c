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
struct request_queue {TYPE_1__* elevator; } ;
struct request {scalar_t__ fifo_time; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  queuelist; } ;
struct cfq_queue {int /*<<< orphan*/  sort_list; struct request* next_rq; } ;
struct cfq_data {struct cfq_queue* active_queue; } ;
struct TYPE_2__ {struct cfq_data* elevator_data; } ;

/* Variables and functions */
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RQ_CFQG (struct request*) ; 
 struct cfq_queue* RQ_CFQQ (struct request*) ; 
 scalar_t__ cfq_cfqq_on_rr (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_del_cfqq_rr (struct cfq_data*,struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_remove_request (struct request*) ; 
 int /*<<< orphan*/  cfqg_stats_update_io_merged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cfq_merged_requests(struct request_queue *q, struct request *rq,
		    struct request *next)
{
	struct cfq_queue *cfqq = RQ_CFQQ(rq);
	struct cfq_data *cfqd = q->elevator->elevator_data;

	/*
	 * reposition in fifo if next is older than rq
	 */
	if (!list_empty(&rq->queuelist) && !list_empty(&next->queuelist) &&
	    next->fifo_time < rq->fifo_time &&
	    cfqq == RQ_CFQQ(next)) {
		list_move(&rq->queuelist, &next->queuelist);
		rq->fifo_time = next->fifo_time;
	}

	if (cfqq->next_rq == next)
		cfqq->next_rq = rq;
	cfq_remove_request(next);
	cfqg_stats_update_io_merged(RQ_CFQG(rq), next->cmd_flags);

	cfqq = RQ_CFQQ(next);
	/*
	 * all requests of this queue are merged to other queues, delete it
	 * from the service tree. If it's the active_queue,
	 * cfq_dispatch_requests() will choose to expire it or do idle
	 */
	if (cfq_cfqq_on_rr(cfqq) && RB_EMPTY_ROOT(&cfqq->sort_list) &&
	    cfqq != cfqd->active_queue)
		cfq_del_cfqq_rr(cfqd, cfqq);
}