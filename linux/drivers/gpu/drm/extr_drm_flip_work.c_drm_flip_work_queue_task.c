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
struct drm_flip_work {int /*<<< orphan*/  lock; int /*<<< orphan*/  queued; } ;
struct drm_flip_task {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void drm_flip_work_queue_task(struct drm_flip_work *work,
			      struct drm_flip_task *task)
{
	unsigned long flags;

	spin_lock_irqsave(&work->lock, flags);
	list_add_tail(&task->node, &work->queued);
	spin_unlock_irqrestore(&work->lock, flags);
}