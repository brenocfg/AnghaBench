#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct jz4780_dma_dev {int /*<<< orphan*/  dma_device; TYPE_3__* chan; int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {int /*<<< orphan*/  task; } ;
struct TYPE_6__ {TYPE_2__ vchan; } ;

/* Variables and functions */
 int JZ_DMA_NR_CHANNELS ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct jz4780_dma_dev*) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct jz4780_dma_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jz4780_dma_remove(struct platform_device *pdev)
{
	struct jz4780_dma_dev *jzdma = platform_get_drvdata(pdev);
	int i;

	of_dma_controller_free(pdev->dev.of_node);

	free_irq(jzdma->irq, jzdma);

	for (i = 0; i < JZ_DMA_NR_CHANNELS; i++)
		tasklet_kill(&jzdma->chan[i].vchan.task);

	dma_async_device_unregister(&jzdma->dma_device);
	return 0;
}