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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc_free; } ;
struct jz4740_dmaengine_chan {unsigned int id; TYPE_1__ vchan; } ;
struct dma_device {int directions; int /*<<< orphan*/  channels; int /*<<< orphan*/ * dev; int /*<<< orphan*/  residue_granularity; void* dst_addr_widths; void* src_addr_widths; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_config; int /*<<< orphan*/  device_prep_dma_cyclic; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  cap_mask; } ;
struct jz4740_dma_dev {int /*<<< orphan*/  clk; struct jz4740_dmaengine_chan* chan; int /*<<< orphan*/  base; struct dma_device ddev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_CYCLIC ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_RESIDUE_GRANULARITY_BURST ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 void* JZ4740_DMA_BUSWIDTHS ; 
 unsigned int JZ_DMA_NR_CHANS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct jz4740_dma_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dma_async_device_register (struct dma_device*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (struct dma_device*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_dma_desc_free ; 
 int /*<<< orphan*/  jz4740_dma_free_chan_resources ; 
 int /*<<< orphan*/  jz4740_dma_irq ; 
 int /*<<< orphan*/  jz4740_dma_issue_pending ; 
 int /*<<< orphan*/  jz4740_dma_prep_dma_cyclic ; 
 int /*<<< orphan*/  jz4740_dma_prep_slave_sg ; 
 int /*<<< orphan*/  jz4740_dma_slave_config ; 
 int /*<<< orphan*/  jz4740_dma_terminate_all ; 
 int /*<<< orphan*/  jz4740_dma_tx_status ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct jz4740_dma_dev*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jz4740_dma_dev*) ; 
 int /*<<< orphan*/  vchan_init (TYPE_1__*,struct dma_device*) ; 

__attribute__((used)) static int jz4740_dma_probe(struct platform_device *pdev)
{
	struct jz4740_dmaengine_chan *chan;
	struct jz4740_dma_dev *dmadev;
	struct dma_device *dd;
	unsigned int i;
	struct resource *res;
	int ret;
	int irq;

	dmadev = devm_kzalloc(&pdev->dev, sizeof(*dmadev), GFP_KERNEL);
	if (!dmadev)
		return -EINVAL;

	dd = &dmadev->ddev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dmadev->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(dmadev->base))
		return PTR_ERR(dmadev->base);

	dmadev->clk = clk_get(&pdev->dev, "dma");
	if (IS_ERR(dmadev->clk))
		return PTR_ERR(dmadev->clk);

	clk_prepare_enable(dmadev->clk);

	dma_cap_set(DMA_SLAVE, dd->cap_mask);
	dma_cap_set(DMA_CYCLIC, dd->cap_mask);
	dd->device_free_chan_resources = jz4740_dma_free_chan_resources;
	dd->device_tx_status = jz4740_dma_tx_status;
	dd->device_issue_pending = jz4740_dma_issue_pending;
	dd->device_prep_slave_sg = jz4740_dma_prep_slave_sg;
	dd->device_prep_dma_cyclic = jz4740_dma_prep_dma_cyclic;
	dd->device_config = jz4740_dma_slave_config;
	dd->device_terminate_all = jz4740_dma_terminate_all;
	dd->src_addr_widths = JZ4740_DMA_BUSWIDTHS;
	dd->dst_addr_widths = JZ4740_DMA_BUSWIDTHS;
	dd->directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	dd->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	dd->dev = &pdev->dev;
	INIT_LIST_HEAD(&dd->channels);

	for (i = 0; i < JZ_DMA_NR_CHANS; i++) {
		chan = &dmadev->chan[i];
		chan->id = i;
		chan->vchan.desc_free = jz4740_dma_desc_free;
		vchan_init(&chan->vchan, dd);
	}

	ret = dma_async_device_register(dd);
	if (ret)
		goto err_clk;

	irq = platform_get_irq(pdev, 0);
	ret = request_irq(irq, jz4740_dma_irq, 0, dev_name(&pdev->dev), dmadev);
	if (ret)
		goto err_unregister;

	platform_set_drvdata(pdev, dmadev);

	return 0;

err_unregister:
	dma_async_device_unregister(dd);
err_clk:
	clk_disable_unprepare(dmadev->clk);
	return ret;
}