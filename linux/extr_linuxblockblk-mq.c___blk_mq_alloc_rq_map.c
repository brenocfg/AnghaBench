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
struct blk_mq_tag_set {int /*<<< orphan*/ ** tags; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  reserved_tags; } ;

/* Variables and functions */
 int /*<<< orphan*/ * blk_mq_alloc_rq_map (struct blk_mq_tag_set*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int blk_mq_alloc_rqs (struct blk_mq_tag_set*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_rq_map (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __blk_mq_alloc_rq_map(struct blk_mq_tag_set *set, int hctx_idx)
{
	int ret = 0;

	set->tags[hctx_idx] = blk_mq_alloc_rq_map(set, hctx_idx,
					set->queue_depth, set->reserved_tags);
	if (!set->tags[hctx_idx])
		return false;

	ret = blk_mq_alloc_rqs(set, set->tags[hctx_idx], hctx_idx,
				set->queue_depth);
	if (!ret)
		return true;

	blk_mq_free_rq_map(set->tags[hctx_idx]);
	set->tags[hctx_idx] = NULL;
	return false;
}