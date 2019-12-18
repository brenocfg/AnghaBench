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
struct v4l2_device {TYPE_1__* mdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct isp_csi2_device {int /*<<< orphan*/  video_out; TYPE_2__ subdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap3isp_csi2_unregister_entities (struct isp_csi2_device*) ; 
 int omap3isp_video_register (int /*<<< orphan*/ *,struct v4l2_device*) ; 
 int v4l2_device_register_subdev (struct v4l2_device*,TYPE_2__*) ; 

int omap3isp_csi2_register_entities(struct isp_csi2_device *csi2,
				    struct v4l2_device *vdev)
{
	int ret;

	/* Register the subdev and video nodes. */
	csi2->subdev.dev = vdev->mdev->dev;
	ret = v4l2_device_register_subdev(vdev, &csi2->subdev);
	if (ret < 0)
		goto error;

	ret = omap3isp_video_register(&csi2->video_out, vdev);
	if (ret < 0)
		goto error;

	return 0;

error:
	omap3isp_csi2_unregister_entities(csi2);
	return ret;
}