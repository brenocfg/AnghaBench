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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct dma_device {int directions; int /*<<< orphan*/  channels; int /*<<< orphan*/  residue_granularity; void* dst_addr_widths; void* src_addr_widths; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_synchronize; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_config; int /*<<< orphan*/  device_prep_dma_memcpy; int /*<<< orphan*/  device_prep_dma_cyclic; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; int /*<<< orphan*/  copy_align; struct device* dev; int /*<<< orphan*/  cap_mask; } ;
struct jz4780_dma_dev {int irq; int /*<<< orphan*/  clk; struct jz4780_dma_chan* chan; struct dma_device dma_device; int /*<<< orphan*/  chan_reserved; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc_free; } ;
struct jz4780_dma_chan {int id; TYPE_1__ vchan; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMAENGINE_ALIGN_4_BYTES ; 
 int /*<<< orphan*/  DMA_CYCLIC ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_RESIDUE_GRANULARITY_BURST ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 void* JZ_DMA_BUSWIDTHS ; 
 int JZ_DMA_DMAC_DMAE ; 
 int JZ_DMA_DMAC_FMSC ; 
 int JZ_DMA_NR_CHANNELS ; 
 int /*<<< orphan*/  JZ_DMA_REG_DMAC ; 
 int /*<<< orphan*/  JZ_DMA_REG_DMACP ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct jz4780_dma_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dma_async_device_register (struct dma_device*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (struct dma_device*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int,struct jz4780_dma_dev*) ; 
 int /*<<< orphan*/  jz4780_dma_alloc_chan_resources ; 
 int /*<<< orphan*/  jz4780_dma_config ; 
 int /*<<< orphan*/  jz4780_dma_desc_free ; 
 int /*<<< orphan*/  jz4780_dma_free_chan_resources ; 
 int /*<<< orphan*/  jz4780_dma_irq_handler ; 
 int /*<<< orphan*/  jz4780_dma_issue_pending ; 
 int /*<<< orphan*/  jz4780_dma_prep_dma_cyclic ; 
 int /*<<< orphan*/  jz4780_dma_prep_dma_memcpy ; 
 int /*<<< orphan*/  jz4780_dma_prep_slave_sg ; 
 int /*<<< orphan*/  jz4780_dma_synchronize ; 
 int /*<<< orphan*/  jz4780_dma_terminate_all ; 
 int /*<<< orphan*/  jz4780_dma_tx_status ; 
 int /*<<< orphan*/  jz4780_dma_writel (struct jz4780_dma_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jz4780_of_dma_xlate ; 
 int of_dma_controller_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jz4780_dma_dev*) ; 
 int /*<<< orphan*/  of_property_read_u32_index (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct jz4780_dma_dev*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jz4780_dma_dev*) ; 
 int /*<<< orphan*/  vchan_init (TYPE_1__*,struct dma_device*) ; 

__attribute__((used)) static int jz4780_dma_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct jz4780_dma_dev *jzdma;
	struct jz4780_dma_chan *jzchan;
	struct dma_device *dd;
	struct resource *res;
	int i, ret;

	if (!dev->of_node) {
		dev_err(dev, "This driver must be probed from devicetree\n");
		return -EINVAL;
	}

	jzdma = devm_kzalloc(dev, sizeof(*jzdma), GFP_KERNEL);
	if (!jzdma)
		return -ENOMEM;

	platform_set_drvdata(pdev, jzdma);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(dev, "failed to get I/O memory\n");
		return -EINVAL;
	}

	jzdma->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(jzdma->base))
		return PTR_ERR(jzdma->base);

	ret = platform_get_irq(pdev, 0);
	if (ret < 0) {
		dev_err(dev, "failed to get IRQ: %d\n", ret);
		return ret;
	}

	jzdma->irq = ret;

	ret = request_irq(jzdma->irq, jz4780_dma_irq_handler, 0, dev_name(dev),
			  jzdma);
	if (ret) {
		dev_err(dev, "failed to request IRQ %u!\n", jzdma->irq);
		return ret;
	}

	jzdma->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(jzdma->clk)) {
		dev_err(dev, "failed to get clock\n");
		ret = PTR_ERR(jzdma->clk);
		goto err_free_irq;
	}

	clk_prepare_enable(jzdma->clk);

	/* Property is optional, if it doesn't exist the value will remain 0. */
	of_property_read_u32_index(dev->of_node, "ingenic,reserved-channels",
				   0, &jzdma->chan_reserved);

	dd = &jzdma->dma_device;

	dma_cap_set(DMA_MEMCPY, dd->cap_mask);
	dma_cap_set(DMA_SLAVE, dd->cap_mask);
	dma_cap_set(DMA_CYCLIC, dd->cap_mask);

	dd->dev = dev;
	dd->copy_align = DMAENGINE_ALIGN_4_BYTES;
	dd->device_alloc_chan_resources = jz4780_dma_alloc_chan_resources;
	dd->device_free_chan_resources = jz4780_dma_free_chan_resources;
	dd->device_prep_slave_sg = jz4780_dma_prep_slave_sg;
	dd->device_prep_dma_cyclic = jz4780_dma_prep_dma_cyclic;
	dd->device_prep_dma_memcpy = jz4780_dma_prep_dma_memcpy;
	dd->device_config = jz4780_dma_config;
	dd->device_terminate_all = jz4780_dma_terminate_all;
	dd->device_synchronize = jz4780_dma_synchronize;
	dd->device_tx_status = jz4780_dma_tx_status;
	dd->device_issue_pending = jz4780_dma_issue_pending;
	dd->src_addr_widths = JZ_DMA_BUSWIDTHS;
	dd->dst_addr_widths = JZ_DMA_BUSWIDTHS;
	dd->directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	dd->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

	/*
	 * Enable DMA controller, mark all channels as not programmable.
	 * Also set the FMSC bit - it increases MSC performance, so it makes
	 * little sense not to enable it.
	 */
	jz4780_dma_writel(jzdma, JZ_DMA_REG_DMAC,
			  JZ_DMA_DMAC_DMAE | JZ_DMA_DMAC_FMSC);
	jz4780_dma_writel(jzdma, JZ_DMA_REG_DMACP, 0);

	INIT_LIST_HEAD(&dd->channels);

	for (i = 0; i < JZ_DMA_NR_CHANNELS; i++) {
		jzchan = &jzdma->chan[i];
		jzchan->id = i;

		vchan_init(&jzchan->vchan, dd);
		jzchan->vchan.desc_free = jz4780_dma_desc_free;
	}

	ret = dma_async_device_register(dd);
	if (ret) {
		dev_err(dev, "failed to register device\n");
		goto err_disable_clk;
	}

	/* Register with OF DMA helpers. */
	ret = of_dma_controller_register(dev->of_node, jz4780_of_dma_xlate,
					 jzdma);
	if (ret) {
		dev_err(dev, "failed to register OF DMA controller\n");
		goto err_unregister_dev;
	}

	dev_info(dev, "JZ4780 DMA controller initialised\n");
	return 0;

err_unregister_dev:
	dma_async_device_unregister(dd);

err_disable_clk:
	clk_disable_unprepare(jzdma->clk);

err_free_irq:
	free_irq(jzdma->irq, jzdma);
	return ret;
}