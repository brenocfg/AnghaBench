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
struct TYPE_4__ {int depth; } ;
struct sbitmap_queue {TYPE_2__ sb; } ;
struct blk_mq_hw_ctx {int flags; int /*<<< orphan*/  nr_active; TYPE_1__* tags; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int /*<<< orphan*/  active_queues; } ;

/* Variables and functions */
 int BLK_MQ_F_TAG_SHARED ; 
 int /*<<< orphan*/  BLK_MQ_S_TAG_ACTIVE ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool hctx_may_queue(struct blk_mq_hw_ctx *hctx,
				  struct sbitmap_queue *bt)
{
	unsigned int depth, users;

	if (!hctx || !(hctx->flags & BLK_MQ_F_TAG_SHARED))
		return true;
	if (!test_bit(BLK_MQ_S_TAG_ACTIVE, &hctx->state))
		return true;

	/*
	 * Don't try dividing an ant
	 */
	if (bt->sb.depth == 1)
		return true;

	users = atomic_read(&hctx->tags->active_queues);
	if (!users)
		return true;

	/*
	 * Allow at least some tags
	 */
	depth = max((bt->sb.depth + users - 1) / users, 4U);
	return atomic_read(&hctx->nr_active) < depth;
}