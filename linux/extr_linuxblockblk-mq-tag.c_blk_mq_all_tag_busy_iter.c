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
struct blk_mq_tags {int /*<<< orphan*/  bitmap_tags; int /*<<< orphan*/  breserved_tags; scalar_t__ nr_reserved_tags; } ;
typedef  int /*<<< orphan*/  busy_tag_iter_fn ;

/* Variables and functions */
 int /*<<< orphan*/  bt_tags_for_each (struct blk_mq_tags*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static void blk_mq_all_tag_busy_iter(struct blk_mq_tags *tags,
		busy_tag_iter_fn *fn, void *priv)
{
	if (tags->nr_reserved_tags)
		bt_tags_for_each(tags, &tags->breserved_tags, fn, priv, true);
	bt_tags_for_each(tags, &tags->bitmap_tags, fn, priv, false);
}