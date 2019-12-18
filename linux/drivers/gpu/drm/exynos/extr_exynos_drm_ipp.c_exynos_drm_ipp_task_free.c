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
struct exynos_drm_ipp_task {TYPE_1__* event; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  dev; } ;
struct exynos_drm_ipp {int /*<<< orphan*/  drm_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_DRIVER (int /*<<< orphan*/ ,char*,struct exynos_drm_ipp_task*) ; 
 int /*<<< orphan*/  drm_event_cancel_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_drm_ipp_task_release_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct exynos_drm_ipp_task*) ; 

__attribute__((used)) static void exynos_drm_ipp_task_free(struct exynos_drm_ipp *ipp,
				 struct exynos_drm_ipp_task *task)
{
	DRM_DEV_DEBUG_DRIVER(task->dev, "Freeing task %pK\n", task);

	exynos_drm_ipp_task_release_buf(&task->src);
	exynos_drm_ipp_task_release_buf(&task->dst);
	if (task->event)
		drm_event_cancel_free(ipp->drm_dev, &task->event->base);
	kfree(task);
}