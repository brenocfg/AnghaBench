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
struct sirfsoc_dma {int /*<<< orphan*/  irq; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  dma; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 struct sirfsoc_dma* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sirfsoc_dma*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (struct device*) ; 
 int /*<<< orphan*/  sirfsoc_dma_runtime_suspend (struct device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sirfsoc_dma_remove(struct platform_device *op)
{
	struct device *dev = &op->dev;
	struct sirfsoc_dma *sdma = dev_get_drvdata(dev);

	of_dma_controller_free(op->dev.of_node);
	dma_async_device_unregister(&sdma->dma);
	free_irq(sdma->irq, sdma);
	tasklet_kill(&sdma->tasklet);
	irq_dispose_mapping(sdma->irq);
	pm_runtime_disable(&op->dev);
	if (!pm_runtime_status_suspended(&op->dev))
		sirfsoc_dma_runtime_suspend(&op->dev);

	return 0;
}