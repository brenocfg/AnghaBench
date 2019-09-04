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
struct v4l2_subdev {int dummy; } ;
struct fimc_pipeline {struct v4l2_subdev** subdevs; } ;
struct exynos_media_pipeline {int dummy; } ;

/* Variables and functions */
 unsigned int IDX_MAX ; 
 struct fimc_pipeline* to_fimc_pipeline (struct exynos_media_pipeline*) ; 

__attribute__((used)) static inline struct v4l2_subdev *__fimc_md_get_subdev(
				struct exynos_media_pipeline *ep,
				unsigned int index)
{
	struct fimc_pipeline *p = to_fimc_pipeline(ep);

	if (!p || index >= IDX_MAX)
		return NULL;
	else
		return p->subdevs[index];
}