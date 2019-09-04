#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request {int tag; unsigned int internal_tag; int cpu; unsigned int cmd_flags; int /*<<< orphan*/  ref; int /*<<< orphan*/ * next_rq; int /*<<< orphan*/ * end_io_data; int /*<<< orphan*/ * end_io; scalar_t__ timeout; int /*<<< orphan*/  timeout_list; scalar_t__ __deadline; scalar_t__ extra_len; int /*<<< orphan*/ * special; scalar_t__ nr_phys_segments; scalar_t__ io_start_time_ns; int /*<<< orphan*/  start_time_ns; int /*<<< orphan*/ * part; int /*<<< orphan*/ * rq_disk; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  hash; int /*<<< orphan*/  queuelist; int /*<<< orphan*/  rq_flags; TYPE_3__* mq_ctx; int /*<<< orphan*/  q; } ;
struct blk_mq_tags {struct request** static_rqs; } ;
struct blk_mq_alloc_data {int flags; TYPE_3__* ctx; int /*<<< orphan*/  q; TYPE_2__* hctx; } ;
typedef  int /*<<< orphan*/  req_flags_t ;
struct TYPE_6__ {int /*<<< orphan*/ * rq_dispatched; } ;
struct TYPE_5__ {int flags; TYPE_1__* tags; int /*<<< orphan*/  nr_active; } ;
struct TYPE_4__ {struct request** rqs; } ;

/* Variables and functions */
 int BLK_MQ_F_TAG_SHARED ; 
 int BLK_MQ_REQ_INTERNAL ; 
 int BLK_MQ_REQ_PREEMPT ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RQF_IO_STAT ; 
 int /*<<< orphan*/  RQF_MQ_INFLIGHT ; 
 int /*<<< orphan*/  RQF_PREEMPT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct blk_mq_tags* blk_mq_tags_from_data (struct blk_mq_alloc_data*) ; 
 scalar_t__ blk_queue_io_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 size_t op_is_sync (unsigned int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct request *blk_mq_rq_ctx_init(struct blk_mq_alloc_data *data,
		unsigned int tag, unsigned int op)
{
	struct blk_mq_tags *tags = blk_mq_tags_from_data(data);
	struct request *rq = tags->static_rqs[tag];
	req_flags_t rq_flags = 0;

	if (data->flags & BLK_MQ_REQ_INTERNAL) {
		rq->tag = -1;
		rq->internal_tag = tag;
	} else {
		if (data->hctx->flags & BLK_MQ_F_TAG_SHARED) {
			rq_flags = RQF_MQ_INFLIGHT;
			atomic_inc(&data->hctx->nr_active);
		}
		rq->tag = tag;
		rq->internal_tag = -1;
		data->hctx->tags->rqs[rq->tag] = rq;
	}

	/* csd/requeue_work/fifo_time is initialized before use */
	rq->q = data->q;
	rq->mq_ctx = data->ctx;
	rq->rq_flags = rq_flags;
	rq->cpu = -1;
	rq->cmd_flags = op;
	if (data->flags & BLK_MQ_REQ_PREEMPT)
		rq->rq_flags |= RQF_PREEMPT;
	if (blk_queue_io_stat(data->q))
		rq->rq_flags |= RQF_IO_STAT;
	INIT_LIST_HEAD(&rq->queuelist);
	INIT_HLIST_NODE(&rq->hash);
	RB_CLEAR_NODE(&rq->rb_node);
	rq->rq_disk = NULL;
	rq->part = NULL;
	rq->start_time_ns = ktime_get_ns();
	rq->io_start_time_ns = 0;
	rq->nr_phys_segments = 0;
#if defined(CONFIG_BLK_DEV_INTEGRITY)
	rq->nr_integrity_segments = 0;
#endif
	rq->special = NULL;
	/* tag was already set */
	rq->extra_len = 0;
	rq->__deadline = 0;

	INIT_LIST_HEAD(&rq->timeout_list);
	rq->timeout = 0;

	rq->end_io = NULL;
	rq->end_io_data = NULL;
	rq->next_rq = NULL;

#ifdef CONFIG_BLK_CGROUP
	rq->rl = NULL;
#endif

	data->ctx->rq_dispatched[op_is_sync(op)]++;
	refcount_set(&rq->ref, 1);
	return rq;
}