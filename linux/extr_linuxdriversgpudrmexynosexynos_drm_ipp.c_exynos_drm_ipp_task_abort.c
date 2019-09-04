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
struct exynos_drm_ipp_task {int flags; int /*<<< orphan*/  head; } ;
struct exynos_drm_ipp {int /*<<< orphan*/  lock; TYPE_1__* funcs; struct exynos_drm_ipp_task* task; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* abort ) (struct exynos_drm_ipp*,struct exynos_drm_ipp_task*) ;} ;

/* Variables and functions */
 int DRM_EXYNOS_IPP_TASK_ASYNC ; 
 int DRM_EXYNOS_IPP_TASK_DONE ; 
 int /*<<< orphan*/  exynos_drm_ipp_task_cleanup (struct exynos_drm_ipp_task*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct exynos_drm_ipp*,struct exynos_drm_ipp_task*) ; 

__attribute__((used)) static void exynos_drm_ipp_task_abort(struct exynos_drm_ipp *ipp,
				      struct exynos_drm_ipp_task *task)
{
	unsigned long flags;

	spin_lock_irqsave(&ipp->lock, flags);
	if (task->flags & DRM_EXYNOS_IPP_TASK_DONE) {
		/* already completed task */
		exynos_drm_ipp_task_cleanup(task);
	} else if (ipp->task != task) {
		/* task has not been scheduled for execution yet */
		list_del_init(&task->head);
		exynos_drm_ipp_task_cleanup(task);
	} else {
		/*
		 * currently processed task, call abort() and perform
		 * cleanup with async worker
		 */
		task->flags |= DRM_EXYNOS_IPP_TASK_ASYNC;
		spin_unlock_irqrestore(&ipp->lock, flags);
		if (ipp->funcs->abort)
			ipp->funcs->abort(ipp, task);
		return;
	}
	spin_unlock_irqrestore(&ipp->lock, flags);
}