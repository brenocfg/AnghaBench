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
struct request_queue {struct request* last_merge; } ;
struct TYPE_4__ {struct TYPE_4__* prev; } ;
struct request {int cmd_flags; TYPE_2__ queuelist; } ;
struct TYPE_3__ {scalar_t__ service; scalar_t__ budget; } ;
struct bfq_queue {int /*<<< orphan*/  meta_pending; int /*<<< orphan*/ * pos_root; int /*<<< orphan*/  pos_node; TYPE_1__ entity; struct request* next_rq; int /*<<< orphan*/  sort_list; int /*<<< orphan*/ * queued; struct bfq_data* bfqd; } ;
struct bfq_data {struct bfq_queue* in_service_queue; int /*<<< orphan*/  queued; } ;

/* Variables and functions */
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int REQ_META ; 
 struct bfq_queue* RQ_BFQQ (struct request*) ; 
 scalar_t__ bfq_bfqq_busy (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_del_bfqq_busy (struct bfq_data*,struct bfq_queue*,int) ; 
 struct request* bfq_find_next_rq (struct bfq_data*,struct bfq_queue*,struct request*) ; 
 int /*<<< orphan*/  bfq_pos_tree_add_move (struct bfq_data*,struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_updated_next_req (struct bfq_data*,struct bfq_queue*) ; 
 int /*<<< orphan*/  elv_rb_del (int /*<<< orphan*/ *,struct request*) ; 
 int /*<<< orphan*/  elv_rqhash_del (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  list_del_init (TYPE_2__*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rq_is_sync (struct request*) ; 

__attribute__((used)) static void bfq_remove_request(struct request_queue *q,
			       struct request *rq)
{
	struct bfq_queue *bfqq = RQ_BFQQ(rq);
	struct bfq_data *bfqd = bfqq->bfqd;
	const int sync = rq_is_sync(rq);

	if (bfqq->next_rq == rq) {
		bfqq->next_rq = bfq_find_next_rq(bfqd, bfqq, rq);
		bfq_updated_next_req(bfqd, bfqq);
	}

	if (rq->queuelist.prev != &rq->queuelist)
		list_del_init(&rq->queuelist);
	bfqq->queued[sync]--;
	bfqd->queued--;
	elv_rb_del(&bfqq->sort_list, rq);

	elv_rqhash_del(q, rq);
	if (q->last_merge == rq)
		q->last_merge = NULL;

	if (RB_EMPTY_ROOT(&bfqq->sort_list)) {
		bfqq->next_rq = NULL;

		if (bfq_bfqq_busy(bfqq) && bfqq != bfqd->in_service_queue) {
			bfq_del_bfqq_busy(bfqd, bfqq, false);
			/*
			 * bfqq emptied. In normal operation, when
			 * bfqq is empty, bfqq->entity.service and
			 * bfqq->entity.budget must contain,
			 * respectively, the service received and the
			 * budget used last time bfqq emptied. These
			 * facts do not hold in this case, as at least
			 * this last removal occurred while bfqq is
			 * not in service. To avoid inconsistencies,
			 * reset both bfqq->entity.service and
			 * bfqq->entity.budget, if bfqq has still a
			 * process that may issue I/O requests to it.
			 */
			bfqq->entity.budget = bfqq->entity.service = 0;
		}

		/*
		 * Remove queue from request-position tree as it is empty.
		 */
		if (bfqq->pos_root) {
			rb_erase(&bfqq->pos_node, bfqq->pos_root);
			bfqq->pos_root = NULL;
		}
	} else {
		bfq_pos_tree_add_move(bfqd, bfqq);
	}

	if (rq->cmd_flags & REQ_META)
		bfqq->meta_pending--;

}