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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mv_xor_v2_device {int desc_size; int /*<<< orphan*/  clk; int /*<<< orphan*/  irq_tasklet; TYPE_1__* msi_desc; int /*<<< orphan*/  hw_desq; int /*<<< orphan*/  hw_desq_virt; int /*<<< orphan*/  dmadev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int MV_XOR_V2_DESC_NUM ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mv_xor_v2_device*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mv_xor_v2_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_msi_domain_free_irqs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mv_xor_v2_remove(struct platform_device *pdev)
{
	struct mv_xor_v2_device *xor_dev = platform_get_drvdata(pdev);

	dma_async_device_unregister(&xor_dev->dmadev);

	dma_free_coherent(&pdev->dev,
			  xor_dev->desc_size * MV_XOR_V2_DESC_NUM,
			  xor_dev->hw_desq_virt, xor_dev->hw_desq);

	devm_free_irq(&pdev->dev, xor_dev->msi_desc->irq, xor_dev);

	platform_msi_domain_free_irqs(&pdev->dev);

	tasklet_kill(&xor_dev->irq_tasklet);

	clk_disable_unprepare(xor_dev->clk);

	return 0;
}