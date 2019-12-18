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
struct v4l2_subdev {int /*<<< orphan*/  grp_id; } ;
struct fimc_md {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  user_subdev_api; struct fimc_dev** fimc; int /*<<< orphan*/ * pmf; } ;
struct TYPE_4__ {int /*<<< orphan*/  user_subdev_api; struct v4l2_subdev subdev; } ;
struct fimc_dev {size_t id; TYPE_2__ vid_cap; TYPE_1__* pdev; } ;
struct exynos_media_pipeline {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 size_t FIMC_MAX_DEVS ; 
 int /*<<< orphan*/  GRP_ID_FIMC ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 struct exynos_media_pipeline* fimc_md_pipeline_create (struct fimc_md*) ; 
 int v4l2_device_register_subdev (int /*<<< orphan*/ *,struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,size_t,int) ; 
 int /*<<< orphan*/  v4l2_set_subdev_hostdata (struct v4l2_subdev*,struct exynos_media_pipeline*) ; 

__attribute__((used)) static int register_fimc_entity(struct fimc_md *fmd, struct fimc_dev *fimc)
{
	struct v4l2_subdev *sd;
	struct exynos_media_pipeline *ep;
	int ret;

	if (WARN_ON(fimc->id >= FIMC_MAX_DEVS || fmd->fimc[fimc->id]))
		return -EBUSY;

	sd = &fimc->vid_cap.subdev;
	sd->grp_id = GRP_ID_FIMC;

	ep = fimc_md_pipeline_create(fmd);
	if (!ep)
		return -ENOMEM;

	v4l2_set_subdev_hostdata(sd, ep);

	ret = v4l2_device_register_subdev(&fmd->v4l2_dev, sd);
	if (!ret) {
		if (!fmd->pmf && fimc->pdev)
			fmd->pmf = &fimc->pdev->dev;
		fmd->fimc[fimc->id] = fimc;
		fimc->vid_cap.user_subdev_api = fmd->user_subdev_api;
	} else {
		v4l2_err(&fmd->v4l2_dev, "Failed to register FIMC.%d (%d)\n",
			 fimc->id, ret);
	}
	return ret;
}