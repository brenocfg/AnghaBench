#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {int /*<<< orphan*/  queuelist; struct request_queue* q; struct blk_mq_ctx* mq_ctx; } ;
struct blk_plug {int /*<<< orphan*/  mq_list; } ;
struct blk_mq_ctx {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  LIST_HEAD (TYPE_1__) ; 
 int /*<<< orphan*/  blk_mq_sched_insert_requests (struct request_queue*,struct blk_mq_ctx*,TYPE_1__*,int) ; 
 TYPE_1__ ctx_list ; 
 TYPE_1__ list ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 struct request* list_entry_rq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_sort (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  plug_ctx_cmp ; 
 int /*<<< orphan*/  trace_block_unplug (struct request_queue*,unsigned int,int) ; 

void blk_mq_flush_plug_list(struct blk_plug *plug, bool from_schedule)
{
	struct blk_mq_ctx *this_ctx;
	struct request_queue *this_q;
	struct request *rq;
	LIST_HEAD(list);
	LIST_HEAD(ctx_list);
	unsigned int depth;

	list_splice_init(&plug->mq_list, &list);

	list_sort(NULL, &list, plug_ctx_cmp);

	this_q = NULL;
	this_ctx = NULL;
	depth = 0;

	while (!list_empty(&list)) {
		rq = list_entry_rq(list.next);
		list_del_init(&rq->queuelist);
		BUG_ON(!rq->q);
		if (rq->mq_ctx != this_ctx) {
			if (this_ctx) {
				trace_block_unplug(this_q, depth, !from_schedule);
				blk_mq_sched_insert_requests(this_q, this_ctx,
								&ctx_list,
								from_schedule);
			}

			this_ctx = rq->mq_ctx;
			this_q = rq->q;
			depth = 0;
		}

		depth++;
		list_add_tail(&rq->queuelist, &ctx_list);
	}

	/*
	 * If 'this_ctx' is set, we know we have entries to complete
	 * on 'ctx_list'. Do those.
	 */
	if (this_ctx) {
		trace_block_unplug(this_q, depth, !from_schedule);
		blk_mq_sched_insert_requests(this_q, this_ctx, &ctx_list,
						from_schedule);
	}
}