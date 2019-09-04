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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct owl_dma {int /*<<< orphan*/  clk; int /*<<< orphan*/  irq; TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  OWL_DMA_IRQ_EN0 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct owl_dma*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  dma_writel (struct owl_dma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  owl_dma_free (struct owl_dma*) ; 
 struct owl_dma* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int owl_dma_remove(struct platform_device *pdev)
{
	struct owl_dma *od = platform_get_drvdata(pdev);

	dma_async_device_unregister(&od->dma);

	/* Mask all interrupts for this execution environment */
	dma_writel(od, OWL_DMA_IRQ_EN0, 0x0);

	/* Make sure we won't have any further interrupts */
	devm_free_irq(od->dma.dev, od->irq, od);

	owl_dma_free(od);

	clk_disable_unprepare(od->clk);

	return 0;
}