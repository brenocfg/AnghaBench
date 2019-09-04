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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct msgdma_device {int /*<<< orphan*/  dmadev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msgdma_dev_remove (struct msgdma_device*) ; 
 struct msgdma_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int msgdma_remove(struct platform_device *pdev)
{
	struct msgdma_device *mdev = platform_get_drvdata(pdev);

	dma_async_device_unregister(&mdev->dmadev);
	msgdma_dev_remove(mdev);

	dev_notice(&pdev->dev, "Altera mSGDMA driver removed\n");

	return 0;
}