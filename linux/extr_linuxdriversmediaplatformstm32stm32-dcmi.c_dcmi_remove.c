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
struct stm32_dcmi {int /*<<< orphan*/  dma_chan; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  notifier; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 struct stm32_dcmi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dcmi_remove(struct platform_device *pdev)
{
	struct stm32_dcmi *dcmi = platform_get_drvdata(pdev);

	pm_runtime_disable(&pdev->dev);

	v4l2_async_notifier_unregister(&dcmi->notifier);
	v4l2_device_unregister(&dcmi->v4l2_dev);

	dma_release_channel(dcmi->dma_chan);

	return 0;
}