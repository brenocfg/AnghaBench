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
struct blk_mq_tags {unsigned int nr_reserved_tags; unsigned int nr_tags; int /*<<< orphan*/  bitmap_tags; } ;
struct blk_mq_tag_set {int dummy; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  queue_num; TYPE_1__* queue; } ;
struct TYPE_2__ {struct blk_mq_tag_set* tag_set; } ;

/* Variables and functions */
 int BLKDEV_MAX_RQ ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct blk_mq_tags* blk_mq_alloc_rq_map (struct blk_mq_tag_set*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int blk_mq_alloc_rqs (struct blk_mq_tag_set*,struct blk_mq_tags*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  blk_mq_free_rq_map (struct blk_mq_tags*) ; 
 int /*<<< orphan*/  blk_mq_free_rqs (struct blk_mq_tag_set*,struct blk_mq_tags*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_queue_resize (int /*<<< orphan*/ *,unsigned int) ; 

int blk_mq_tag_update_depth(struct blk_mq_hw_ctx *hctx,
			    struct blk_mq_tags **tagsptr, unsigned int tdepth,
			    bool can_grow)
{
	struct blk_mq_tags *tags = *tagsptr;

	if (tdepth <= tags->nr_reserved_tags)
		return -EINVAL;

	/*
	 * If we are allowed to grow beyond the original size, allocate
	 * a new set of tags before freeing the old one.
	 */
	if (tdepth > tags->nr_tags) {
		struct blk_mq_tag_set *set = hctx->queue->tag_set;
		struct blk_mq_tags *new;
		bool ret;

		if (!can_grow)
			return -EINVAL;

		/*
		 * We need some sort of upper limit, set it high enough that
		 * no valid use cases should require more.
		 */
		if (tdepth > 16 * BLKDEV_MAX_RQ)
			return -EINVAL;

		new = blk_mq_alloc_rq_map(set, hctx->queue_num, tdepth,
				tags->nr_reserved_tags);
		if (!new)
			return -ENOMEM;
		ret = blk_mq_alloc_rqs(set, new, hctx->queue_num, tdepth);
		if (ret) {
			blk_mq_free_rq_map(new);
			return -ENOMEM;
		}

		blk_mq_free_rqs(set, *tagsptr, hctx->queue_num);
		blk_mq_free_rq_map(*tagsptr);
		*tagsptr = new;
	} else {
		/*
		 * Don't need (or can't) update reserved tags here, they
		 * remain static and should never need resizing.
		 */
		sbitmap_queue_resize(&tags->bitmap_tags,
				tdepth - tags->nr_reserved_tags);
	}

	return 0;
}