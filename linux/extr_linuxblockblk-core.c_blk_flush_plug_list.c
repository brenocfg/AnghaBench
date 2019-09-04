#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {int /*<<< orphan*/  cmd_flags; struct request_queue* q; int /*<<< orphan*/  queuelist; } ;
struct TYPE_7__ {int /*<<< orphan*/  next; } ;
struct blk_plug {TYPE_1__ list; TYPE_1__ mq_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ELEVATOR_INSERT_FLUSH ; 
 int /*<<< orphan*/  ELEVATOR_INSERT_SORT_MERGE ; 
 int /*<<< orphan*/  LIST_HEAD (TYPE_1__) ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __elv_add_request (struct request_queue*,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_flush_plug_list (struct blk_plug*,int) ; 
 int /*<<< orphan*/  blk_queue_dying (struct request_queue*) ; 
 int /*<<< orphan*/  flush_plug_callbacks (struct blk_plug*,int) ; 
 TYPE_1__ list ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (TYPE_1__*) ; 
 struct request* list_entry_rq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_sort (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_splice_init (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ op_is_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plug_rq_cmp ; 
 int /*<<< orphan*/  queue_unplugged (struct request_queue*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void blk_flush_plug_list(struct blk_plug *plug, bool from_schedule)
{
	struct request_queue *q;
	struct request *rq;
	LIST_HEAD(list);
	unsigned int depth;

	flush_plug_callbacks(plug, from_schedule);

	if (!list_empty(&plug->mq_list))
		blk_mq_flush_plug_list(plug, from_schedule);

	if (list_empty(&plug->list))
		return;

	list_splice_init(&plug->list, &list);

	list_sort(NULL, &list, plug_rq_cmp);

	q = NULL;
	depth = 0;

	while (!list_empty(&list)) {
		rq = list_entry_rq(list.next);
		list_del_init(&rq->queuelist);
		BUG_ON(!rq->q);
		if (rq->q != q) {
			/*
			 * This drops the queue lock
			 */
			if (q)
				queue_unplugged(q, depth, from_schedule);
			q = rq->q;
			depth = 0;
			spin_lock_irq(q->queue_lock);
		}

		/*
		 * Short-circuit if @q is dead
		 */
		if (unlikely(blk_queue_dying(q))) {
			__blk_end_request_all(rq, BLK_STS_IOERR);
			continue;
		}

		/*
		 * rq is already accounted, so use raw insert
		 */
		if (op_is_flush(rq->cmd_flags))
			__elv_add_request(q, rq, ELEVATOR_INSERT_FLUSH);
		else
			__elv_add_request(q, rq, ELEVATOR_INSERT_SORT_MERGE);

		depth++;
	}

	/*
	 * This drops the queue lock
	 */
	if (q)
		queue_unplugged(q, depth, from_schedule);
}