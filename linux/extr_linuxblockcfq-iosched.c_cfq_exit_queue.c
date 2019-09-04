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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct elevator_queue {struct cfq_data* elevator_data; } ;
struct cfq_data {struct cfq_data* root_group; scalar_t__ active_queue; struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cfq_slice_expired (struct cfq_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_shutdown_timer_wq (struct cfq_data*) ; 
 int /*<<< orphan*/  kfree (struct cfq_data*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfq_exit_queue(struct elevator_queue *e)
{
	struct cfq_data *cfqd = e->elevator_data;
	struct request_queue *q = cfqd->queue;

	cfq_shutdown_timer_wq(cfqd);

	spin_lock_irq(q->queue_lock);

	if (cfqd->active_queue)
		__cfq_slice_expired(cfqd, cfqd->active_queue, 0);

	spin_unlock_irq(q->queue_lock);

	cfq_shutdown_timer_wq(cfqd);

#ifdef CONFIG_CFQ_GROUP_IOSCHED
	blkcg_deactivate_policy(q, &blkcg_policy_cfq);
#else
	kfree(cfqd->root_group);
#endif
	kfree(cfqd);
}