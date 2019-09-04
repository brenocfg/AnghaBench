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
struct device {scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct edma_cc {int /*<<< orphan*/  dummy_slot; int /*<<< orphan*/ * dma_memcpy; int /*<<< orphan*/  dma_slave; int /*<<< orphan*/  ccerrint; int /*<<< orphan*/  ccint; } ;

/* Variables and functions */
 struct edma_cc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  devm_free_irq (struct device*,int /*<<< orphan*/ ,struct edma_cc*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edma_cleanupp_vchan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edma_free_slot (struct edma_cc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_dma_controller_free (scalar_t__) ; 

__attribute__((used)) static int edma_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct edma_cc *ecc = dev_get_drvdata(dev);

	devm_free_irq(dev, ecc->ccint, ecc);
	devm_free_irq(dev, ecc->ccerrint, ecc);

	edma_cleanupp_vchan(&ecc->dma_slave);

	if (dev->of_node)
		of_dma_controller_free(dev->of_node);
	dma_async_device_unregister(&ecc->dma_slave);
	if (ecc->dma_memcpy)
		dma_async_device_unregister(ecc->dma_memcpy);
	edma_free_slot(ecc, ecc->dummy_slot);

	return 0;
}