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
struct exynos_drm_ipp_task {int /*<<< orphan*/  head; } ;
struct exynos_drm_ipp {int /*<<< orphan*/  lock; int /*<<< orphan*/  todo_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  exynos_drm_ipp_next_task (struct exynos_drm_ipp*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void exynos_drm_ipp_schedule_task(struct exynos_drm_ipp *ipp,
					 struct exynos_drm_ipp_task *task)
{
	unsigned long flags;

	spin_lock_irqsave(&ipp->lock, flags);
	list_add(&task->head, &ipp->todo_list);
	spin_unlock_irqrestore(&ipp->lock, flags);

	exynos_drm_ipp_next_task(ipp);
}