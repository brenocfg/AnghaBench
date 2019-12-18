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
struct pxa_camera_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/ * mclk_clk; int /*<<< orphan*/  notifier; int /*<<< orphan*/ * dma_chans; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct pxa_camera_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa_camera_deactivate (struct pxa_camera_dev*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_clk_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxa_camera_remove(struct platform_device *pdev)
{
	struct pxa_camera_dev *pcdev = dev_get_drvdata(&pdev->dev);

	pxa_camera_deactivate(pcdev);
	dma_release_channel(pcdev->dma_chans[0]);
	dma_release_channel(pcdev->dma_chans[1]);
	dma_release_channel(pcdev->dma_chans[2]);

	v4l2_async_notifier_unregister(&pcdev->notifier);
	v4l2_async_notifier_cleanup(&pcdev->notifier);

	if (pcdev->mclk_clk) {
		v4l2_clk_unregister(pcdev->mclk_clk);
		pcdev->mclk_clk = NULL;
	}

	v4l2_device_unregister(&pcdev->v4l2_dev);

	dev_info(&pdev->dev, "PXA Camera driver unloaded\n");

	return 0;
}