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
struct request_queue {TYPE_1__* elevator; } ;
struct request {int dummy; } ;
struct cfq_queue {int /*<<< orphan*/  nr_sectors; int /*<<< orphan*/  dispatched; int /*<<< orphan*/  next_rq; } ;
struct cfq_data {int /*<<< orphan*/ * rq_in_flight; } ;
struct TYPE_4__ {int /*<<< orphan*/  dispatched; } ;
struct TYPE_3__ {struct cfq_data* elevator_data; } ;

/* Variables and functions */
 TYPE_2__* RQ_CFQG (struct request*) ; 
 struct cfq_queue* RQ_CFQQ (struct request*) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 
 size_t cfq_cfqq_sync (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_find_next_rq (struct cfq_data*,struct cfq_queue*,struct request*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*) ; 
 int /*<<< orphan*/  cfq_remove_request (struct request*) ; 
 int /*<<< orphan*/  elv_dispatch_sort (struct request_queue*,struct request*) ; 

__attribute__((used)) static void cfq_dispatch_insert(struct request_queue *q, struct request *rq)
{
	struct cfq_data *cfqd = q->elevator->elevator_data;
	struct cfq_queue *cfqq = RQ_CFQQ(rq);

	cfq_log_cfqq(cfqd, cfqq, "dispatch_insert");

	cfqq->next_rq = cfq_find_next_rq(cfqd, cfqq, rq);
	cfq_remove_request(rq);
	cfqq->dispatched++;
	(RQ_CFQG(rq))->dispatched++;
	elv_dispatch_sort(q, rq);

	cfqd->rq_in_flight[cfq_cfqq_sync(cfqq)]++;
	cfqq->nr_sectors += blk_rq_sectors(rq);
}