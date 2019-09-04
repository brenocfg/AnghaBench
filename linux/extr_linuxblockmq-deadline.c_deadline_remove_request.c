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
struct request_queue {struct request* last_merge; TYPE_1__* elevator; } ;
struct request {int /*<<< orphan*/  rb_node; int /*<<< orphan*/  queuelist; } ;
struct deadline_data {int dummy; } ;
struct TYPE_2__ {struct deadline_data* elevator_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deadline_del_rq_rb (struct deadline_data*,struct request*) ; 
 int /*<<< orphan*/  elv_rqhash_del (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void deadline_remove_request(struct request_queue *q, struct request *rq)
{
	struct deadline_data *dd = q->elevator->elevator_data;

	list_del_init(&rq->queuelist);

	/*
	 * We might not be on the rbtree, if we are doing an insert merge
	 */
	if (!RB_EMPTY_NODE(&rq->rb_node))
		deadline_del_rq_rb(dd, rq);

	elv_rqhash_del(q, rq);
	if (q->last_merge == rq)
		q->last_merge = NULL;
}