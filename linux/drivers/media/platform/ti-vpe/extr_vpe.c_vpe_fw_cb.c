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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct video_device {int /*<<< orphan*/  num; TYPE_1__* v4l2_dev; int /*<<< orphan*/ * lock; } ;
struct vpe_dev {TYPE_1__ v4l2_dev; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  dev_mutex; struct video_device vfd; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct vpe_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct vpe_dev*) ; 
 int /*<<< orphan*/  vpe_err (struct vpe_dev*,char*) ; 
 int /*<<< orphan*/  vpe_runtime_put (struct platform_device*) ; 
 int /*<<< orphan*/  vpe_set_clock_enable (struct vpe_dev*,int /*<<< orphan*/ ) ; 
 struct video_device vpe_videodev ; 

__attribute__((used)) static void vpe_fw_cb(struct platform_device *pdev)
{
	struct vpe_dev *dev = platform_get_drvdata(pdev);
	struct video_device *vfd;
	int ret;

	vfd = &dev->vfd;
	*vfd = vpe_videodev;
	vfd->lock = &dev->dev_mutex;
	vfd->v4l2_dev = &dev->v4l2_dev;

	ret = video_register_device(vfd, VFL_TYPE_GRABBER, 0);
	if (ret) {
		vpe_err(dev, "Failed to register video device\n");

		vpe_set_clock_enable(dev, 0);
		vpe_runtime_put(pdev);
		pm_runtime_disable(&pdev->dev);
		v4l2_m2m_release(dev->m2m_dev);
		v4l2_device_unregister(&dev->v4l2_dev);

		return;
	}

	video_set_drvdata(vfd, dev);
	dev_info(dev->v4l2_dev.dev, "Device registered as /dev/video%d\n",
		vfd->num);
}