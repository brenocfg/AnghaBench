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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {int /*<<< orphan*/  v4l2_dev; } ;
struct pxa_camera_dev {int /*<<< orphan*/  mlock; int /*<<< orphan*/ * sensor; int /*<<< orphan*/  vdev; int /*<<< orphan*/ * mclk_clk; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CICR0 ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcdev_to_dev (struct pxa_camera_dev*) ; 
 int /*<<< orphan*/  pxa_camera_destroy_formats (struct pxa_camera_dev*) ; 
 int /*<<< orphan*/  pxa_dma_stop_channels (struct pxa_camera_dev*) ; 
 int /*<<< orphan*/  v4l2_clk_unregister (int /*<<< orphan*/ *) ; 
 struct pxa_camera_dev* v4l2_dev_to_pcdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pxa_camera_sensor_unbind(struct v4l2_async_notifier *notifier,
		     struct v4l2_subdev *subdev,
		     struct v4l2_async_subdev *asd)
{
	struct pxa_camera_dev *pcdev = v4l2_dev_to_pcdev(notifier->v4l2_dev);

	mutex_lock(&pcdev->mlock);
	dev_info(pcdev_to_dev(pcdev),
		 "PXA Camera driver detached from camera %s\n",
		 subdev->name);

	/* disable capture, disable interrupts */
	__raw_writel(0x3ff, pcdev->base + CICR0);

	/* Stop DMA engine */
	pxa_dma_stop_channels(pcdev);

	pxa_camera_destroy_formats(pcdev);

	if (pcdev->mclk_clk) {
		v4l2_clk_unregister(pcdev->mclk_clk);
		pcdev->mclk_clk = NULL;
	}

	video_unregister_device(&pcdev->vdev);
	pcdev->sensor = NULL;

	mutex_unlock(&pcdev->mlock);
}