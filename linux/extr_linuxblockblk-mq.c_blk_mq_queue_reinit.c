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
struct request_queue {int /*<<< orphan*/  mq_freeze_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_debugfs_register_hctxs (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_debugfs_unregister_hctxs (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_map_swqueue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_sysfs_register (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_sysfs_unregister (struct request_queue*) ; 

__attribute__((used)) static void blk_mq_queue_reinit(struct request_queue *q)
{
	WARN_ON_ONCE(!atomic_read(&q->mq_freeze_depth));

	blk_mq_debugfs_unregister_hctxs(q);
	blk_mq_sysfs_unregister(q);

	/*
	 * redo blk_mq_init_cpu_queues and blk_mq_init_hw_queues. FIXME: maybe
	 * we should change hctx numa_node according to the new topology (this
	 * involves freeing and re-allocating memory, worth doing?)
	 */
	blk_mq_map_swqueue(q);

	blk_mq_sysfs_register(q);
	blk_mq_debugfs_register_hctxs(q);
}