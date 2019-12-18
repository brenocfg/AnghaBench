#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct fimc_md {int /*<<< orphan*/  v4l2_dev; TYPE_6__* fimc_is; TYPE_4__* csis; struct fimc_lite** fimc_lite; struct fimc_dev** fimc; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pipe; } ;
struct fimc_lite {TYPE_3__ ve; int /*<<< orphan*/  subdev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pipe; } ;
struct TYPE_8__ {TYPE_1__ ve; int /*<<< orphan*/  subdev; } ;
struct fimc_dev {TYPE_2__ vid_cap; } ;
struct TYPE_11__ {int /*<<< orphan*/  subdev; } ;
struct TYPE_12__ {TYPE_5__ isp; } ;
struct TYPE_10__ {int /*<<< orphan*/ * sd; } ;

/* Variables and functions */
 int CSIS_MAX_ENTITIES ; 
 int FIMC_LITE_MAX_DEVS ; 
 int FIMC_MAX_DEVS ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void fimc_md_unregister_entities(struct fimc_md *fmd)
{
	int i;

	for (i = 0; i < FIMC_MAX_DEVS; i++) {
		struct fimc_dev *dev = fmd->fimc[i];
		if (dev == NULL)
			continue;
		v4l2_device_unregister_subdev(&dev->vid_cap.subdev);
		dev->vid_cap.ve.pipe = NULL;
		fmd->fimc[i] = NULL;
	}
	for (i = 0; i < FIMC_LITE_MAX_DEVS; i++) {
		struct fimc_lite *dev = fmd->fimc_lite[i];
		if (dev == NULL)
			continue;
		v4l2_device_unregister_subdev(&dev->subdev);
		dev->ve.pipe = NULL;
		fmd->fimc_lite[i] = NULL;
	}
	for (i = 0; i < CSIS_MAX_ENTITIES; i++) {
		if (fmd->csis[i].sd == NULL)
			continue;
		v4l2_device_unregister_subdev(fmd->csis[i].sd);
		fmd->csis[i].sd = NULL;
	}

	if (fmd->fimc_is)
		v4l2_device_unregister_subdev(&fmd->fimc_is->isp.subdev);

	v4l2_info(&fmd->v4l2_dev, "Unregistered all entities\n");
}