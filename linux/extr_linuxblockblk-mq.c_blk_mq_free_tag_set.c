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
struct blk_mq_tag_set {int /*<<< orphan*/ * tags; int /*<<< orphan*/ * mq_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_free_map_and_requests (struct blk_mq_tag_set*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int nr_cpu_ids ; 

void blk_mq_free_tag_set(struct blk_mq_tag_set *set)
{
	int i;

	for (i = 0; i < nr_cpu_ids; i++)
		blk_mq_free_map_and_requests(set, i);

	kfree(set->mq_map);
	set->mq_map = NULL;

	kfree(set->tags);
	set->tags = NULL;
}