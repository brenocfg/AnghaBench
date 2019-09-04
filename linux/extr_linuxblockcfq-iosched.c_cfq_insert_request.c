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
struct request {int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  queuelist; scalar_t__ fifo_time; } ;
struct cfq_queue {int /*<<< orphan*/  fifo; } ;
struct cfq_data {int /*<<< orphan*/  serving_group; scalar_t__* cfq_fifo_expire; } ;
struct TYPE_2__ {struct cfq_data* elevator_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_CFQG (struct request*) ; 
 struct cfq_queue* RQ_CFQQ (struct request*) ; 
 int /*<<< orphan*/  RQ_CIC (struct request*) ; 
 int /*<<< orphan*/  cfq_add_rq_rb (struct request*) ; 
 int /*<<< orphan*/  cfq_init_prio_data (struct cfq_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*) ; 
 int /*<<< orphan*/  cfq_rq_enqueued (struct cfq_data*,struct cfq_queue*,struct request*) ; 
 int /*<<< orphan*/  cfqg_stats_update_io_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_get_ns () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t rq_is_sync (struct request*) ; 

__attribute__((used)) static void cfq_insert_request(struct request_queue *q, struct request *rq)
{
	struct cfq_data *cfqd = q->elevator->elevator_data;
	struct cfq_queue *cfqq = RQ_CFQQ(rq);

	cfq_log_cfqq(cfqd, cfqq, "insert_request");
	cfq_init_prio_data(cfqq, RQ_CIC(rq));

	rq->fifo_time = ktime_get_ns() + cfqd->cfq_fifo_expire[rq_is_sync(rq)];
	list_add_tail(&rq->queuelist, &cfqq->fifo);
	cfq_add_rq_rb(rq);
	cfqg_stats_update_io_add(RQ_CFQG(rq), cfqd->serving_group,
				 rq->cmd_flags);
	cfq_rq_enqueued(cfqd, cfqq, rq);
}