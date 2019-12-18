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
struct v4l2_device {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  virt; } ;
struct aspeed_video {TYPE_1__ jpeg; int /*<<< orphan*/  dev; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  queue; int /*<<< orphan*/  vdev; int /*<<< orphan*/  eclk; int /*<<< orphan*/  vclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  VE_JPEG_HEADER_SIZE ; 
 int /*<<< orphan*/  aspeed_video_off (struct aspeed_video*) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct v4l2_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_reserved_mem_device_release (struct device*) ; 
 struct aspeed_video* to_aspeed_video (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (struct v4l2_device*) ; 
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aspeed_video_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct v4l2_device *v4l2_dev = dev_get_drvdata(dev);
	struct aspeed_video *video = to_aspeed_video(v4l2_dev);

	aspeed_video_off(video);

	clk_unprepare(video->vclk);
	clk_unprepare(video->eclk);

	video_unregister_device(&video->vdev);

	vb2_queue_release(&video->queue);

	v4l2_ctrl_handler_free(&video->ctrl_handler);

	v4l2_device_unregister(v4l2_dev);

	dma_free_coherent(video->dev, VE_JPEG_HEADER_SIZE, video->jpeg.virt,
			  video->jpeg.dma);

	of_reserved_mem_device_release(dev);

	return 0;
}