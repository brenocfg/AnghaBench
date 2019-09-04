#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_12__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  desc_free; } ;
struct mtk_hsdma_vchan {int /*<<< orphan*/  desc_hw_processing; int /*<<< orphan*/  issue_completion; TYPE_1__ vc; } ;
struct dma_device {int /*<<< orphan*/  channels; TYPE_2__* dev; int /*<<< orphan*/  residue_granularity; int /*<<< orphan*/  directions; void* dst_addr_widths; void* src_addr_widths; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_prep_dma_memcpy; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; int /*<<< orphan*/  copy_align; int /*<<< orphan*/  cap_mask; } ;
struct mtk_hsdma_device {int dma_requests; int /*<<< orphan*/  irq; struct mtk_hsdma_vchan* vc; void* pc; int /*<<< orphan*/  lock; int /*<<< orphan*/  pc_refcnt; int /*<<< orphan*/  clk; int /*<<< orphan*/  soc; int /*<<< orphan*/  base; struct dma_device ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_MEM_TO_MEM ; 
 int /*<<< orphan*/  DMA_RESIDUE_GRANULARITY_SEGMENT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_HSDMA_ALIGN_SIZE ; 
 void* MTK_HSDMA_DMA_BUSWIDTHS ; 
 int MTK_HSDMA_NR_MAX_PCHANS ; 
 int MTK_HSDMA_NR_VCHANS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,...) ; 
 int dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 void* devm_kcalloc (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 struct mtk_hsdma_device* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct mtk_hsdma_device*) ; 
 int dma_async_device_register (struct dma_device*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (struct dma_device*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_hsdma_alloc_chan_resources ; 
 int /*<<< orphan*/  mtk_hsdma_free_chan_resources ; 
 int /*<<< orphan*/  mtk_hsdma_hw_init (struct mtk_hsdma_device*) ; 
 int /*<<< orphan*/  mtk_hsdma_irq ; 
 int /*<<< orphan*/  mtk_hsdma_issue_pending ; 
 int /*<<< orphan*/  mtk_hsdma_prep_dma_memcpy ; 
 int /*<<< orphan*/  mtk_hsdma_terminate_all ; 
 int /*<<< orphan*/  mtk_hsdma_tx_status ; 
 int /*<<< orphan*/  mtk_hsdma_vdesc_free ; 
 int /*<<< orphan*/  of_device_get_match_data (TYPE_2__*) ; 
 int of_dma_controller_register (scalar_t__,int /*<<< orphan*/ ,struct mtk_hsdma_device*) ; 
 int /*<<< orphan*/  of_dma_xlate_by_chan_id ; 
 scalar_t__ of_property_read_u32 (scalar_t__,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_hsdma_device*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_init (TYPE_1__*,struct dma_device*) ; 

__attribute__((used)) static int mtk_hsdma_probe(struct platform_device *pdev)
{
	struct mtk_hsdma_device *hsdma;
	struct mtk_hsdma_vchan *vc;
	struct dma_device *dd;
	struct resource *res;
	int i, err;

	hsdma = devm_kzalloc(&pdev->dev, sizeof(*hsdma), GFP_KERNEL);
	if (!hsdma)
		return -ENOMEM;

	dd = &hsdma->ddev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hsdma->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hsdma->base))
		return PTR_ERR(hsdma->base);

	hsdma->soc = of_device_get_match_data(&pdev->dev);
	if (!hsdma->soc) {
		dev_err(&pdev->dev, "No device match found\n");
		return -ENODEV;
	}

	hsdma->clk = devm_clk_get(&pdev->dev, "hsdma");
	if (IS_ERR(hsdma->clk)) {
		dev_err(&pdev->dev, "No clock for %s\n",
			dev_name(&pdev->dev));
		return PTR_ERR(hsdma->clk);
	}

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res) {
		dev_err(&pdev->dev, "No irq resource for %s\n",
			dev_name(&pdev->dev));
		return -EINVAL;
	}
	hsdma->irq = res->start;

	refcount_set(&hsdma->pc_refcnt, 0);
	spin_lock_init(&hsdma->lock);

	dma_cap_set(DMA_MEMCPY, dd->cap_mask);

	dd->copy_align = MTK_HSDMA_ALIGN_SIZE;
	dd->device_alloc_chan_resources = mtk_hsdma_alloc_chan_resources;
	dd->device_free_chan_resources = mtk_hsdma_free_chan_resources;
	dd->device_tx_status = mtk_hsdma_tx_status;
	dd->device_issue_pending = mtk_hsdma_issue_pending;
	dd->device_prep_dma_memcpy = mtk_hsdma_prep_dma_memcpy;
	dd->device_terminate_all = mtk_hsdma_terminate_all;
	dd->src_addr_widths = MTK_HSDMA_DMA_BUSWIDTHS;
	dd->dst_addr_widths = MTK_HSDMA_DMA_BUSWIDTHS;
	dd->directions = BIT(DMA_MEM_TO_MEM);
	dd->residue_granularity = DMA_RESIDUE_GRANULARITY_SEGMENT;
	dd->dev = &pdev->dev;
	INIT_LIST_HEAD(&dd->channels);

	hsdma->dma_requests = MTK_HSDMA_NR_VCHANS;
	if (pdev->dev.of_node && of_property_read_u32(pdev->dev.of_node,
						      "dma-requests",
						      &hsdma->dma_requests)) {
		dev_info(&pdev->dev,
			 "Using %u as missing dma-requests property\n",
			 MTK_HSDMA_NR_VCHANS);
	}

	hsdma->pc = devm_kcalloc(&pdev->dev, MTK_HSDMA_NR_MAX_PCHANS,
				 sizeof(*hsdma->pc), GFP_KERNEL);
	if (!hsdma->pc)
		return -ENOMEM;

	hsdma->vc = devm_kcalloc(&pdev->dev, hsdma->dma_requests,
				 sizeof(*hsdma->vc), GFP_KERNEL);
	if (!hsdma->vc)
		return -ENOMEM;

	for (i = 0; i < hsdma->dma_requests; i++) {
		vc = &hsdma->vc[i];
		vc->vc.desc_free = mtk_hsdma_vdesc_free;
		vchan_init(&vc->vc, dd);
		init_completion(&vc->issue_completion);
		INIT_LIST_HEAD(&vc->desc_hw_processing);
	}

	err = dma_async_device_register(dd);
	if (err)
		return err;

	err = of_dma_controller_register(pdev->dev.of_node,
					 of_dma_xlate_by_chan_id, hsdma);
	if (err) {
		dev_err(&pdev->dev,
			"MediaTek HSDMA OF registration failed %d\n", err);
		goto err_unregister;
	}

	mtk_hsdma_hw_init(hsdma);

	err = devm_request_irq(&pdev->dev, hsdma->irq,
			       mtk_hsdma_irq, 0,
			       dev_name(&pdev->dev), hsdma);
	if (err) {
		dev_err(&pdev->dev,
			"request_irq failed with err %d\n", err);
		goto err_unregister;
	}

	platform_set_drvdata(pdev, hsdma);

	dev_info(&pdev->dev, "MediaTek HSDMA driver registered\n");

	return 0;

err_unregister:
	dma_async_device_unregister(dd);

	return err;
}