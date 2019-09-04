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
struct workqueue_struct {int dummy; } ;
struct drm_flip_work {int /*<<< orphan*/  worker; int /*<<< orphan*/  lock; int /*<<< orphan*/  queued; int /*<<< orphan*/  commited; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (struct workqueue_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void drm_flip_work_commit(struct drm_flip_work *work,
		struct workqueue_struct *wq)
{
	unsigned long flags;

	spin_lock_irqsave(&work->lock, flags);
	list_splice_tail(&work->queued, &work->commited);
	INIT_LIST_HEAD(&work->queued);
	spin_unlock_irqrestore(&work->lock, flags);
	queue_work(wq, &work->worker);
}