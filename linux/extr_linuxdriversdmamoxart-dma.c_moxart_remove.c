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
struct TYPE_2__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct moxart_dmadev {int /*<<< orphan*/  dma_slave; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (TYPE_1__*,int /*<<< orphan*/ ,struct moxart_dmadev*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_dma_controller_free (scalar_t__) ; 
 struct moxart_dmadev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int moxart_remove(struct platform_device *pdev)
{
	struct moxart_dmadev *m = platform_get_drvdata(pdev);

	devm_free_irq(&pdev->dev, m->irq, m);

	dma_async_device_unregister(&m->dma_slave);

	if (pdev->dev.of_node)
		of_dma_controller_free(pdev->dev.of_node);

	return 0;
}