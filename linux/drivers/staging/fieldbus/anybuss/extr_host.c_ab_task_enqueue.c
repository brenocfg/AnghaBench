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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
typedef  int /*<<< orphan*/  t ;
struct kfifo {int dummy; } ;
struct ab_task {int /*<<< orphan*/  start_jiffies; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __ab_task_get (struct ab_task*) ; 
 int /*<<< orphan*/  ab_task_put (struct ab_task*) ; 
 int /*<<< orphan*/  jiffies ; 
 int kfifo_in_spinlocked (struct kfifo*,struct ab_task**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ab_task_enqueue(struct ab_task *t, struct kfifo *q, spinlock_t *slock,
		wait_queue_head_t *wq)
{
	int ret;

	t->start_jiffies = jiffies;
	__ab_task_get(t);
	ret = kfifo_in_spinlocked(q, &t, sizeof(t), slock);
	if (!ret) {
		ab_task_put(t);
		return -ENOMEM;
	}
	wake_up(wq);
	return 0;
}