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
struct xgene_dma {int /*<<< orphan*/  clk; int /*<<< orphan*/ * chan; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int XGENE_DMA_MAX_CHANNEL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct xgene_dma* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xgene_dma*) ; 
 int /*<<< orphan*/  xgene_dma_delete_chan_rings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgene_dma_free_irqs (struct xgene_dma*) ; 
 int xgene_dma_get_resources (struct platform_device*,struct xgene_dma*) ; 
 int xgene_dma_init_async (struct xgene_dma*) ; 
 int /*<<< orphan*/  xgene_dma_init_channels (struct xgene_dma*) ; 
 int /*<<< orphan*/  xgene_dma_init_hw (struct xgene_dma*) ; 
 int xgene_dma_init_mem (struct xgene_dma*) ; 
 int xgene_dma_init_rings (struct xgene_dma*) ; 
 int xgene_dma_request_irqs (struct xgene_dma*) ; 

__attribute__((used)) static int xgene_dma_probe(struct platform_device *pdev)
{
	struct xgene_dma *pdma;
	int ret, i;

	pdma = devm_kzalloc(&pdev->dev, sizeof(*pdma), GFP_KERNEL);
	if (!pdma)
		return -ENOMEM;

	pdma->dev = &pdev->dev;
	platform_set_drvdata(pdev, pdma);

	ret = xgene_dma_get_resources(pdev, pdma);
	if (ret)
		return ret;

	pdma->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(pdma->clk) && !ACPI_COMPANION(&pdev->dev)) {
		dev_err(&pdev->dev, "Failed to get clk\n");
		return PTR_ERR(pdma->clk);
	}

	/* Enable clk before accessing registers */
	if (!IS_ERR(pdma->clk)) {
		ret = clk_prepare_enable(pdma->clk);
		if (ret) {
			dev_err(&pdev->dev, "Failed to enable clk %d\n", ret);
			return ret;
		}
	}

	/* Remove DMA RAM out of shutdown */
	ret = xgene_dma_init_mem(pdma);
	if (ret)
		goto err_clk_enable;

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(42));
	if (ret) {
		dev_err(&pdev->dev, "No usable DMA configuration\n");
		goto err_dma_mask;
	}

	/* Initialize DMA channels software state */
	xgene_dma_init_channels(pdma);

	/* Configue DMA rings */
	ret = xgene_dma_init_rings(pdma);
	if (ret)
		goto err_clk_enable;

	ret = xgene_dma_request_irqs(pdma);
	if (ret)
		goto err_request_irq;

	/* Configure and enable DMA engine */
	xgene_dma_init_hw(pdma);

	/* Register DMA device with linux async framework */
	ret = xgene_dma_init_async(pdma);
	if (ret)
		goto err_async_init;

	return 0;

err_async_init:
	xgene_dma_free_irqs(pdma);

err_request_irq:
	for (i = 0; i < XGENE_DMA_MAX_CHANNEL; i++)
		xgene_dma_delete_chan_rings(&pdma->chan[i]);

err_dma_mask:
err_clk_enable:
	if (!IS_ERR(pdma->clk))
		clk_disable_unprepare(pdma->clk);

	return ret;
}