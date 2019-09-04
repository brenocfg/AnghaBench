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
struct nullb_cmd {int dummy; } ;
struct nullb {TYPE_1__* dev; } ;
struct blk_mq_tag_set {int cmd_size; int /*<<< orphan*/  flags; int /*<<< orphan*/ * driver_data; int /*<<< orphan*/  numa_node; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  nr_hw_queues; int /*<<< orphan*/ * ops; } ;
struct TYPE_2__ {scalar_t__ blocking; int /*<<< orphan*/  home_node; int /*<<< orphan*/  hw_queue_depth; int /*<<< orphan*/  submit_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_F_BLOCKING ; 
 int /*<<< orphan*/  BLK_MQ_F_NO_SCHED ; 
 int /*<<< orphan*/  BLK_MQ_F_SHOULD_MERGE ; 
 int blk_mq_alloc_tag_set (struct blk_mq_tag_set*) ; 
 scalar_t__ g_blocking ; 
 int /*<<< orphan*/  g_home_node ; 
 int /*<<< orphan*/  g_hw_queue_depth ; 
 scalar_t__ g_no_sched ; 
 int /*<<< orphan*/  g_submit_queues ; 
 int /*<<< orphan*/  null_mq_ops ; 

__attribute__((used)) static int null_init_tag_set(struct nullb *nullb, struct blk_mq_tag_set *set)
{
	set->ops = &null_mq_ops;
	set->nr_hw_queues = nullb ? nullb->dev->submit_queues :
						g_submit_queues;
	set->queue_depth = nullb ? nullb->dev->hw_queue_depth :
						g_hw_queue_depth;
	set->numa_node = nullb ? nullb->dev->home_node : g_home_node;
	set->cmd_size	= sizeof(struct nullb_cmd);
	set->flags = BLK_MQ_F_SHOULD_MERGE;
	if (g_no_sched)
		set->flags |= BLK_MQ_F_NO_SCHED;
	set->driver_data = NULL;

	if ((nullb && nullb->dev->blocking) || g_blocking)
		set->flags |= BLK_MQ_F_BLOCKING;

	return blk_mq_alloc_tag_set(set);
}