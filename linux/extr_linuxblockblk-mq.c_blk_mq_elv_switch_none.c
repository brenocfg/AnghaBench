#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  sysfs_lock; TYPE_2__* elevator; } ;
struct list_head {int dummy; } ;
struct blk_mq_qe_pair {TYPE_1__* type; int /*<<< orphan*/  node; struct request_queue* q; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  elevator_owner; } ;

/* Variables and functions */
 int GFP_NOIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elevator_switch_mq (struct request_queue*,int /*<<< orphan*/ *) ; 
 struct blk_mq_qe_pair* kmalloc (int,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool blk_mq_elv_switch_none(struct list_head *head,
		struct request_queue *q)
{
	struct blk_mq_qe_pair *qe;

	if (!q->elevator)
		return true;

	qe = kmalloc(sizeof(*qe), GFP_NOIO | __GFP_NOWARN | __GFP_NORETRY);
	if (!qe)
		return false;

	INIT_LIST_HEAD(&qe->node);
	qe->q = q;
	qe->type = q->elevator->type;
	list_add(&qe->node, head);

	mutex_lock(&q->sysfs_lock);
	/*
	 * After elevator_switch_mq, the previous elevator_queue will be
	 * released by elevator_release. The reference of the io scheduler
	 * module get by elevator_get will also be put. So we need to get
	 * a reference of the io scheduler module here to prevent it to be
	 * removed.
	 */
	__module_get(qe->type->elevator_owner);
	elevator_switch_mq(q, NULL);
	mutex_unlock(&q->sysfs_lock);

	return true;
}