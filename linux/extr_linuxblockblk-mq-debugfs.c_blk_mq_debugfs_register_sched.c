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
struct request_queue {int /*<<< orphan*/  sched_debugfs_dir; int /*<<< orphan*/  debugfs_dir; TYPE_1__* elevator; } ;
struct elevator_type {int /*<<< orphan*/  queue_debugfs_attrs; } ;
struct TYPE_2__ {struct elevator_type* type; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  blk_mq_debugfs_unregister_sched (struct request_queue*) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_files (int /*<<< orphan*/ ,struct request_queue*,int /*<<< orphan*/ ) ; 

int blk_mq_debugfs_register_sched(struct request_queue *q)
{
	struct elevator_type *e = q->elevator->type;

	if (!q->debugfs_dir)
		return -ENOENT;

	if (!e->queue_debugfs_attrs)
		return 0;

	q->sched_debugfs_dir = debugfs_create_dir("sched", q->debugfs_dir);
	if (!q->sched_debugfs_dir)
		return -ENOMEM;

	if (!debugfs_create_files(q->sched_debugfs_dir, q,
				  e->queue_debugfs_attrs))
		goto err;

	return 0;

err:
	blk_mq_debugfs_unregister_sched(q);
	return -ENOMEM;
}