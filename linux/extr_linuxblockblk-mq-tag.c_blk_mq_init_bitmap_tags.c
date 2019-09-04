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
struct blk_mq_tags {unsigned int nr_tags; unsigned int nr_reserved_tags; int /*<<< orphan*/  bitmap_tags; int /*<<< orphan*/  breserved_tags; } ;

/* Variables and functions */
 int BLK_TAG_ALLOC_RR ; 
 scalar_t__ bt_alloc (int /*<<< orphan*/ *,unsigned int,int,int) ; 
 int /*<<< orphan*/  kfree (struct blk_mq_tags*) ; 
 int /*<<< orphan*/  sbitmap_queue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct blk_mq_tags *blk_mq_init_bitmap_tags(struct blk_mq_tags *tags,
						   int node, int alloc_policy)
{
	unsigned int depth = tags->nr_tags - tags->nr_reserved_tags;
	bool round_robin = alloc_policy == BLK_TAG_ALLOC_RR;

	if (bt_alloc(&tags->bitmap_tags, depth, round_robin, node))
		goto free_tags;
	if (bt_alloc(&tags->breserved_tags, tags->nr_reserved_tags, round_robin,
		     node))
		goto free_bitmap_tags;

	return tags;
free_bitmap_tags:
	sbitmap_queue_free(&tags->bitmap_tags);
free_tags:
	kfree(tags);
	return NULL;
}