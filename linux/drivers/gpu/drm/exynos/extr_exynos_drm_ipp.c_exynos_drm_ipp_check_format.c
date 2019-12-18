#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct exynos_drm_ipp_task {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipp; } ;
struct exynos_drm_ipp_formats {int /*<<< orphan*/  num_limits; int /*<<< orphan*/  limits; } ;
struct TYPE_3__ {unsigned int width; scalar_t__ height; unsigned int* pitch; int /*<<< orphan*/ * gem_id; int /*<<< orphan*/  fourcc; int /*<<< orphan*/  modifier; } ;
struct exynos_drm_ipp_buffer {int /*<<< orphan*/  rect; TYPE_1__ buf; TYPE_2__* format; } ;
struct TYPE_4__ {int num_planes; unsigned int* cpp; int /*<<< orphan*/  hsub; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEV_DEBUG_DRIVER (int /*<<< orphan*/ ,char*,struct exynos_drm_ipp_task*,char*) ; 
 int /*<<< orphan*/  DRM_EXYNOS_IPP_FORMAT_DESTINATION ; 
 int /*<<< orphan*/  DRM_EXYNOS_IPP_FORMAT_SOURCE ; 
 int EINVAL ; 
 int ENOENT ; 
 struct exynos_drm_ipp_formats* __ipp_format_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* drm_format_info (int /*<<< orphan*/ ) ; 
 int exynos_drm_ipp_check_scale_limits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int exynos_drm_ipp_check_size_limits (struct exynos_drm_ipp_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int exynos_drm_ipp_check_format(struct exynos_drm_ipp_task *task,
				       struct exynos_drm_ipp_buffer *buf,
				       struct exynos_drm_ipp_buffer *src,
				       struct exynos_drm_ipp_buffer *dst,
				       bool rotate, bool swap)
{
	const struct exynos_drm_ipp_formats *fmt;
	int ret, i;

	fmt = __ipp_format_get(task->ipp, buf->buf.fourcc, buf->buf.modifier,
			       buf == src ? DRM_EXYNOS_IPP_FORMAT_SOURCE :
					    DRM_EXYNOS_IPP_FORMAT_DESTINATION);
	if (!fmt) {
		DRM_DEV_DEBUG_DRIVER(task->dev,
				     "Task %pK: %s format not supported\n",
				     task, buf == src ? "src" : "dst");
		return -EINVAL;
	}

	/* basic checks */
	if (buf->buf.width == 0 || buf->buf.height == 0)
		return -EINVAL;

	buf->format = drm_format_info(buf->buf.fourcc);
	for (i = 0; i < buf->format->num_planes; i++) {
		unsigned int width = (i == 0) ? buf->buf.width :
			     DIV_ROUND_UP(buf->buf.width, buf->format->hsub);

		if (buf->buf.pitch[i] == 0)
			buf->buf.pitch[i] = width * buf->format->cpp[i];
		if (buf->buf.pitch[i] < width * buf->format->cpp[i])
			return -EINVAL;
		if (!buf->buf.gem_id[i])
			return -ENOENT;
	}

	/* pitch for additional planes must match */
	if (buf->format->num_planes > 2 &&
	    buf->buf.pitch[1] != buf->buf.pitch[2])
		return -EINVAL;

	/* check driver limits */
	ret = exynos_drm_ipp_check_size_limits(buf, fmt->limits,
					       fmt->num_limits,
					       rotate,
					       buf == dst ? swap : false);
	if (ret)
		return ret;
	ret = exynos_drm_ipp_check_scale_limits(&src->rect, &dst->rect,
						fmt->limits,
						fmt->num_limits, swap);
	return ret;
}