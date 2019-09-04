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
struct timb_dma {int /*<<< orphan*/  membase; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  dma; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct timb_dma*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct timb_dma*) ; 
 struct timb_dma* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int td_remove(struct platform_device *pdev)
{
	struct timb_dma *td = platform_get_drvdata(pdev);
	struct resource *iomem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	int irq = platform_get_irq(pdev, 0);

	dma_async_device_unregister(&td->dma);
	free_irq(irq, td);
	tasklet_kill(&td->tasklet);
	iounmap(td->membase);
	kfree(td);
	release_mem_region(iomem->start, resource_size(iomem));

	dev_dbg(&pdev->dev, "Removed...\n");
	return 0;
}