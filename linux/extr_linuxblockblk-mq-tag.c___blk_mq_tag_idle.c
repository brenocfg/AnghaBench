#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct blk_mq_tags {int /*<<< orphan*/  active_queues; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  state; struct blk_mq_tags* tags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_S_TAG_ACTIVE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_tag_wakeup_all (struct blk_mq_tags*,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __blk_mq_tag_idle(struct blk_mq_hw_ctx *hctx)
{
	struct blk_mq_tags *tags = hctx->tags;

	if (!test_and_clear_bit(BLK_MQ_S_TAG_ACTIVE, &hctx->state))
		return;

	atomic_dec(&tags->active_queues);

	blk_mq_tag_wakeup_all(tags, false);
}