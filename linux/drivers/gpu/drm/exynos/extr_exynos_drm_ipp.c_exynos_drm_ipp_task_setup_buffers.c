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
struct exynos_drm_ipp_buffer {int dummy; } ;
struct exynos_drm_ipp_task {int /*<<< orphan*/  dev; struct exynos_drm_ipp_buffer dst; struct exynos_drm_ipp_buffer src; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_DRIVER (int /*<<< orphan*/ ,char*,struct exynos_drm_ipp_task*) ; 
 int exynos_drm_ipp_task_setup_buffer (struct exynos_drm_ipp_buffer*,struct drm_file*) ; 

__attribute__((used)) static int exynos_drm_ipp_task_setup_buffers(struct exynos_drm_ipp_task *task,
				     struct drm_file *filp)
{
	struct exynos_drm_ipp_buffer *src = &task->src, *dst = &task->dst;
	int ret = 0;

	DRM_DEV_DEBUG_DRIVER(task->dev, "Setting buffer for task %pK\n",
			     task);

	ret = exynos_drm_ipp_task_setup_buffer(src, filp);
	if (ret) {
		DRM_DEV_DEBUG_DRIVER(task->dev,
				     "Task %pK: src buffer setup failed\n",
				     task);
		return ret;
	}
	ret = exynos_drm_ipp_task_setup_buffer(dst, filp);
	if (ret) {
		DRM_DEV_DEBUG_DRIVER(task->dev,
				     "Task %pK: dst buffer setup failed\n",
				     task);
		return ret;
	}

	DRM_DEV_DEBUG_DRIVER(task->dev, "Task %pK: buffers prepared.\n",
			     task);

	return ret;
}