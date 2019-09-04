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
struct platform_device {int dummy; } ;
struct jz4740_dma_dev {int /*<<< orphan*/  clk; int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct jz4740_dma_dev*) ; 
 int /*<<< orphan*/  jz4740_cleanup_vchan (int /*<<< orphan*/ *) ; 
 struct jz4740_dma_dev* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jz4740_dma_remove(struct platform_device *pdev)
{
	struct jz4740_dma_dev *dmadev = platform_get_drvdata(pdev);
	int irq = platform_get_irq(pdev, 0);

	free_irq(irq, dmadev);

	jz4740_cleanup_vchan(&dmadev->ddev);
	dma_async_device_unregister(&dmadev->ddev);
	clk_disable_unprepare(dmadev->clk);

	return 0;
}