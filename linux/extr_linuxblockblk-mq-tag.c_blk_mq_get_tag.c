#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sbq_wait_state {int /*<<< orphan*/  wait; } ;
struct sbitmap_queue {int dummy; } ;
struct blk_mq_tags {unsigned int nr_reserved_tags; struct sbitmap_queue bitmap_tags; struct sbitmap_queue breserved_tags; } ;
struct blk_mq_alloc_data {int flags; TYPE_1__* ctx; int /*<<< orphan*/  hctx; int /*<<< orphan*/  q; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int BLK_MQ_REQ_NOWAIT ; 
 int BLK_MQ_REQ_RESERVED ; 
 unsigned int BLK_MQ_TAG_FAIL ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __blk_mq_get_tag (struct blk_mq_alloc_data*,struct sbitmap_queue*) ; 
 TYPE_1__* blk_mq_get_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_map_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_put_ctx (TYPE_1__*) ; 
 int /*<<< orphan*/  blk_mq_run_hw_queue (int /*<<< orphan*/ ,int) ; 
 struct blk_mq_tags* blk_mq_tags_from_data (struct blk_mq_alloc_data*) ; 
 struct sbq_wait_state* bt_wait_ptr (struct sbitmap_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_queue_wake_up (struct sbitmap_queue*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait ; 

unsigned int blk_mq_get_tag(struct blk_mq_alloc_data *data)
{
	struct blk_mq_tags *tags = blk_mq_tags_from_data(data);
	struct sbitmap_queue *bt;
	struct sbq_wait_state *ws;
	DEFINE_WAIT(wait);
	unsigned int tag_offset;
	bool drop_ctx;
	int tag;

	if (data->flags & BLK_MQ_REQ_RESERVED) {
		if (unlikely(!tags->nr_reserved_tags)) {
			WARN_ON_ONCE(1);
			return BLK_MQ_TAG_FAIL;
		}
		bt = &tags->breserved_tags;
		tag_offset = 0;
	} else {
		bt = &tags->bitmap_tags;
		tag_offset = tags->nr_reserved_tags;
	}

	tag = __blk_mq_get_tag(data, bt);
	if (tag != -1)
		goto found_tag;

	if (data->flags & BLK_MQ_REQ_NOWAIT)
		return BLK_MQ_TAG_FAIL;

	ws = bt_wait_ptr(bt, data->hctx);
	drop_ctx = data->ctx == NULL;
	do {
		struct sbitmap_queue *bt_prev;

		/*
		 * We're out of tags on this hardware queue, kick any
		 * pending IO submits before going to sleep waiting for
		 * some to complete.
		 */
		blk_mq_run_hw_queue(data->hctx, false);

		/*
		 * Retry tag allocation after running the hardware queue,
		 * as running the queue may also have found completions.
		 */
		tag = __blk_mq_get_tag(data, bt);
		if (tag != -1)
			break;

		prepare_to_wait_exclusive(&ws->wait, &wait,
						TASK_UNINTERRUPTIBLE);

		tag = __blk_mq_get_tag(data, bt);
		if (tag != -1)
			break;

		if (data->ctx)
			blk_mq_put_ctx(data->ctx);

		bt_prev = bt;
		io_schedule();

		data->ctx = blk_mq_get_ctx(data->q);
		data->hctx = blk_mq_map_queue(data->q, data->ctx->cpu);
		tags = blk_mq_tags_from_data(data);
		if (data->flags & BLK_MQ_REQ_RESERVED)
			bt = &tags->breserved_tags;
		else
			bt = &tags->bitmap_tags;

		finish_wait(&ws->wait, &wait);

		/*
		 * If destination hw queue is changed, fake wake up on
		 * previous queue for compensating the wake up miss, so
		 * other allocations on previous queue won't be starved.
		 */
		if (bt != bt_prev)
			sbitmap_queue_wake_up(bt_prev);

		ws = bt_wait_ptr(bt, data->hctx);
	} while (1);

	if (drop_ctx && data->ctx)
		blk_mq_put_ctx(data->ctx);

	finish_wait(&ws->wait, &wait);

found_tag:
	return tag + tag_offset;
}