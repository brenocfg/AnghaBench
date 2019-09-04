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
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  task; TYPE_1__ chan; } ;
struct mtk_hsdma_vchan {TYPE_2__ vc; } ;
struct mtk_hsdma_device {int dma_requests; int /*<<< orphan*/  ddev; int /*<<< orphan*/  irq; struct mtk_hsdma_vchan* vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_HSDMA_INT_ENABLE ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_dma_write (struct mtk_hsdma_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hsdma_hw_deinit (struct mtk_hsdma_device*) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct mtk_hsdma_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_hsdma_remove(struct platform_device *pdev)
{
	struct mtk_hsdma_device *hsdma = platform_get_drvdata(pdev);
	struct mtk_hsdma_vchan *vc;
	int i;

	/* Kill VC task */
	for (i = 0; i < hsdma->dma_requests; i++) {
		vc = &hsdma->vc[i];

		list_del(&vc->vc.chan.device_node);
		tasklet_kill(&vc->vc.task);
	}

	/* Disable DMA interrupt */
	mtk_dma_write(hsdma, MTK_HSDMA_INT_ENABLE, 0);

	/* Waits for any pending IRQ handlers to complete */
	synchronize_irq(hsdma->irq);

	/* Disable hardware */
	mtk_hsdma_hw_deinit(hsdma);

	dma_async_device_unregister(&hsdma->ddev);
	of_dma_controller_free(pdev->dev.of_node);

	return 0;
}