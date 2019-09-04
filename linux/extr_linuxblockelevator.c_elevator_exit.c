#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct elevator_queue {int /*<<< orphan*/  kobj; int /*<<< orphan*/  sysfs_lock; TYPE_4__* type; scalar_t__ uses_mq; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* elevator_exit_fn ) (struct elevator_queue*) ;} ;
struct TYPE_6__ {scalar_t__ exit_sched; } ;
struct TYPE_7__ {TYPE_1__ sq; TYPE_2__ mq; } ;
struct TYPE_8__ {TYPE_3__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_exit_sched (struct request_queue*,struct elevator_queue*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct elevator_queue*) ; 

void elevator_exit(struct request_queue *q, struct elevator_queue *e)
{
	mutex_lock(&e->sysfs_lock);
	if (e->uses_mq && e->type->ops.mq.exit_sched)
		blk_mq_exit_sched(q, e);
	else if (!e->uses_mq && e->type->ops.sq.elevator_exit_fn)
		e->type->ops.sq.elevator_exit_fn(e);
	mutex_unlock(&e->sysfs_lock);

	kobject_put(&e->kobj);
}