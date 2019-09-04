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
struct request_queue {int nr_hw_queues; int /*<<< orphan*/  sysfs_lock; int /*<<< orphan*/  elevator; } ;
struct elevator_type {int dummy; } ;

/* Variables and functions */
 int blk_mq_init_sched (struct request_queue*,struct elevator_type*) ; 
 struct elevator_type* elevator_get (struct request_queue*,char*,int) ; 
 int /*<<< orphan*/  elevator_put (struct elevator_type*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int elevator_init_mq(struct request_queue *q)
{
	struct elevator_type *e;
	int err = 0;

	if (q->nr_hw_queues != 1)
		return 0;

	/*
	 * q->sysfs_lock must be held to provide mutual exclusion between
	 * elevator_switch() and here.
	 */
	mutex_lock(&q->sysfs_lock);
	if (unlikely(q->elevator))
		goto out_unlock;

	e = elevator_get(q, "mq-deadline", false);
	if (!e)
		goto out_unlock;

	err = blk_mq_init_sched(q, e);
	if (err)
		elevator_put(e);
out_unlock:
	mutex_unlock(&q->sysfs_lock);
	return err;
}