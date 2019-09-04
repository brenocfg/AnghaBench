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
struct sbitmap_queue {int /*<<< orphan*/  sb; } ;
struct bt_tags_iter_data {void* data; int reserved; int /*<<< orphan*/ * fn; struct blk_mq_tags* tags; } ;
struct blk_mq_tags {scalar_t__ rqs; } ;
typedef  int /*<<< orphan*/  busy_tag_iter_fn ;

/* Variables and functions */
 int /*<<< orphan*/  bt_tags_iter ; 
 int /*<<< orphan*/  sbitmap_for_each_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bt_tags_iter_data*) ; 

__attribute__((used)) static void bt_tags_for_each(struct blk_mq_tags *tags, struct sbitmap_queue *bt,
			     busy_tag_iter_fn *fn, void *data, bool reserved)
{
	struct bt_tags_iter_data iter_data = {
		.tags = tags,
		.fn = fn,
		.data = data,
		.reserved = reserved,
	};

	if (tags->rqs)
		sbitmap_for_each_set(&bt->sb, bt_tags_iter, &iter_data);
}