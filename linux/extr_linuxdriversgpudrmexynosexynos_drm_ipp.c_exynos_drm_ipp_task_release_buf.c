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
struct exynos_drm_ipp_buffer {int /*<<< orphan*/ * exynos_gem; TYPE_1__* format; } ;
struct TYPE_2__ {int num_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  exynos_drm_gem_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_drm_ipp_task_release_buf(struct exynos_drm_ipp_buffer *buf)
{
	int i;

	if (!buf->exynos_gem[0])
		return;
	for (i = 0; i < buf->format->num_planes; i++)
		exynos_drm_gem_put(buf->exynos_gem[i]);
}