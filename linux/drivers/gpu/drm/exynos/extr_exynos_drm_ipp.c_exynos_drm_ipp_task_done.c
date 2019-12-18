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
struct exynos_drm_ipp_task {int flags; int ret; int /*<<< orphan*/  cleanup_work; int /*<<< orphan*/  dev; struct exynos_drm_ipp* ipp; } ;
struct exynos_drm_ipp {int /*<<< orphan*/  done_wq; int /*<<< orphan*/  lock; struct exynos_drm_ipp_task* task; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_DRIVER (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct exynos_drm_ipp_task*,int) ; 
 int DRM_EXYNOS_IPP_TASK_ASYNC ; 
 int DRM_EXYNOS_IPP_TASK_DONE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_drm_ipp_cleanup_work ; 
 int /*<<< orphan*/  exynos_drm_ipp_next_task (struct exynos_drm_ipp*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void exynos_drm_ipp_task_done(struct exynos_drm_ipp_task *task, int ret)
{
	struct exynos_drm_ipp *ipp = task->ipp;
	unsigned long flags;

	DRM_DEV_DEBUG_DRIVER(task->dev, "ipp: %d, task %pK done: %d\n",
			     ipp->id, task, ret);

	spin_lock_irqsave(&ipp->lock, flags);
	if (ipp->task == task)
		ipp->task = NULL;
	task->flags |= DRM_EXYNOS_IPP_TASK_DONE;
	task->ret = ret;
	spin_unlock_irqrestore(&ipp->lock, flags);

	exynos_drm_ipp_next_task(ipp);
	wake_up(&ipp->done_wq);

	if (task->flags & DRM_EXYNOS_IPP_TASK_ASYNC) {
		INIT_WORK(&task->cleanup_work, exynos_drm_ipp_cleanup_work);
		schedule_work(&task->cleanup_work);
	}
}