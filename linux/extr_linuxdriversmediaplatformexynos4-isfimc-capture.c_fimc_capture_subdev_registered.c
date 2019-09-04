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
struct v4l2_subdev {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pipe; } ;
struct TYPE_4__ {TYPE_1__ ve; } ;
struct fimc_dev {TYPE_2__ vid_cap; } ;

/* Variables and functions */
 int ENXIO ; 
 int fimc_register_capture_device (struct fimc_dev*,int /*<<< orphan*/ ) ; 
 int fimc_register_m2m_device (struct fimc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_unregister_m2m_device (struct fimc_dev*) ; 
 int /*<<< orphan*/ * v4l2_get_subdev_hostdata (struct v4l2_subdev*) ; 
 struct fimc_dev* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int fimc_capture_subdev_registered(struct v4l2_subdev *sd)
{
	struct fimc_dev *fimc = v4l2_get_subdevdata(sd);
	int ret;

	if (fimc == NULL)
		return -ENXIO;

	ret = fimc_register_m2m_device(fimc, sd->v4l2_dev);
	if (ret)
		return ret;

	fimc->vid_cap.ve.pipe = v4l2_get_subdev_hostdata(sd);

	ret = fimc_register_capture_device(fimc, sd->v4l2_dev);
	if (ret) {
		fimc_unregister_m2m_device(fimc);
		fimc->vid_cap.ve.pipe = NULL;
	}

	return ret;
}