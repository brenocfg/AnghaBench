#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int rotation; } ;
struct TYPE_6__ {scalar_t__ width; scalar_t__ height; scalar_t__ fourcc; } ;
struct TYPE_5__ {scalar_t__ w; scalar_t__ h; scalar_t__ x; scalar_t__ y; } ;
struct exynos_drm_ipp_buffer {TYPE_3__ buf; TYPE_2__ rect; } ;
struct exynos_drm_ipp_task {int /*<<< orphan*/  dev; TYPE_1__ transform; struct exynos_drm_ipp_buffer dst; struct exynos_drm_ipp_buffer src; struct exynos_drm_ipp* ipp; } ;
struct exynos_drm_ipp {int capabilities; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_DRIVER (int /*<<< orphan*/ ,char*,struct exynos_drm_ipp_task*) ; 
 int DRM_EXYNOS_IPP_CAP_CONVERT ; 
 int DRM_EXYNOS_IPP_CAP_CROP ; 
 int DRM_EXYNOS_IPP_CAP_ROTATE ; 
 int DRM_EXYNOS_IPP_CAP_SCALE ; 
 unsigned int DRM_MODE_ROTATE_0 ; 
 int EINVAL ; 
 scalar_t__ UINT_MAX ; 
 int drm_rotation_90_or_270 (unsigned int) ; 
 int exynos_drm_ipp_check_format (struct exynos_drm_ipp_task*,struct exynos_drm_ipp_buffer*,struct exynos_drm_ipp_buffer*,struct exynos_drm_ipp_buffer*,int,int) ; 

__attribute__((used)) static int exynos_drm_ipp_task_check(struct exynos_drm_ipp_task *task)
{
	struct exynos_drm_ipp *ipp = task->ipp;
	struct exynos_drm_ipp_buffer *src = &task->src, *dst = &task->dst;
	unsigned int rotation = task->transform.rotation;
	int ret = 0;
	bool swap = drm_rotation_90_or_270(rotation);
	bool rotate = (rotation != DRM_MODE_ROTATE_0);
	bool scale = false;

	DRM_DEV_DEBUG_DRIVER(task->dev, "Checking task %pK\n", task);

	if (src->rect.w == UINT_MAX)
		src->rect.w = src->buf.width;
	if (src->rect.h == UINT_MAX)
		src->rect.h = src->buf.height;
	if (dst->rect.w == UINT_MAX)
		dst->rect.w = dst->buf.width;
	if (dst->rect.h == UINT_MAX)
		dst->rect.h = dst->buf.height;

	if (src->rect.x + src->rect.w > (src->buf.width) ||
	    src->rect.y + src->rect.h > (src->buf.height) ||
	    dst->rect.x + dst->rect.w > (dst->buf.width) ||
	    dst->rect.y + dst->rect.h > (dst->buf.height)) {
		DRM_DEV_DEBUG_DRIVER(task->dev,
				     "Task %pK: defined area is outside provided buffers\n",
				     task);
		return -EINVAL;
	}

	if ((!swap && (src->rect.w != dst->rect.w ||
		       src->rect.h != dst->rect.h)) ||
	    (swap && (src->rect.w != dst->rect.h ||
		      src->rect.h != dst->rect.w)))
		scale = true;

	if ((!(ipp->capabilities & DRM_EXYNOS_IPP_CAP_CROP) &&
	     (src->rect.x || src->rect.y || dst->rect.x || dst->rect.y)) ||
	    (!(ipp->capabilities & DRM_EXYNOS_IPP_CAP_ROTATE) && rotate) ||
	    (!(ipp->capabilities & DRM_EXYNOS_IPP_CAP_SCALE) && scale) ||
	    (!(ipp->capabilities & DRM_EXYNOS_IPP_CAP_CONVERT) &&
	     src->buf.fourcc != dst->buf.fourcc)) {
		DRM_DEV_DEBUG_DRIVER(task->dev, "Task %pK: hw capabilities exceeded\n",
				     task);
		return -EINVAL;
	}

	ret = exynos_drm_ipp_check_format(task, src, src, dst, rotate, swap);
	if (ret)
		return ret;

	ret = exynos_drm_ipp_check_format(task, dst, src, dst, false, swap);
	if (ret)
		return ret;

	DRM_DEV_DEBUG_DRIVER(ipp->dev, "Task %pK: all checks done.\n",
			     task);

	return ret;
}