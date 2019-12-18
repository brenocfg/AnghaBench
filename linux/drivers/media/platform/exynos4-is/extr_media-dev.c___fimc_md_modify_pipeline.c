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
struct TYPE_2__ {scalar_t__ use_count; } ;
struct video_device {TYPE_1__ entity; } ;
struct media_entity {int dummy; } ;
struct fimc_pipeline {int /*<<< orphan*/ ** subdevs; } ;
struct exynos_video_entity {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 size_t IDX_SENSOR ; 
 int __fimc_pipeline_close (int /*<<< orphan*/ ) ; 
 int __fimc_pipeline_open (int /*<<< orphan*/ ,struct media_entity*,int) ; 
 struct video_device* media_entity_to_video_device (struct media_entity*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 struct fimc_pipeline* to_fimc_pipeline (int /*<<< orphan*/ ) ; 
 struct exynos_video_entity* vdev_to_exynos_video_entity (struct video_device*) ; 

__attribute__((used)) static int __fimc_md_modify_pipeline(struct media_entity *entity, bool enable)
{
	struct exynos_video_entity *ve;
	struct fimc_pipeline *p;
	struct video_device *vdev;
	int ret;

	vdev = media_entity_to_video_device(entity);
	if (vdev->entity.use_count == 0)
		return 0;

	ve = vdev_to_exynos_video_entity(vdev);
	p = to_fimc_pipeline(ve->pipe);
	/*
	 * Nothing to do if we are disabling the pipeline, some link
	 * has been disconnected and p->subdevs array is cleared now.
	 */
	if (!enable && p->subdevs[IDX_SENSOR] == NULL)
		return 0;

	if (enable)
		ret = __fimc_pipeline_open(ve->pipe, entity, true);
	else
		ret = __fimc_pipeline_close(ve->pipe);

	if (ret == 0 && !enable)
		memset(p->subdevs, 0, sizeof(p->subdevs));

	return ret;
}