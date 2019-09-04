#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct dma_device {int src_addr_widths; int dst_addr_widths; int directions; int /*<<< orphan*/  channels; int /*<<< orphan*/  device_synchronize; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_pause; int /*<<< orphan*/  device_config; int /*<<< orphan*/  device_prep_dma_cyclic; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_prep_dma_memcpy; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; int /*<<< orphan*/  residue_granularity; int /*<<< orphan*/  copy_align; TYPE_1__* dev; int /*<<< orphan*/  cap_mask; } ;
struct rcar_dmac {unsigned int n_channels; int /*<<< orphan*/ * channels; struct dma_device engine; int /*<<< orphan*/  iomem; TYPE_1__* dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; scalar_t__ iommu_group; } ;
struct platform_device {TYPE_1__ dev; } ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_RESIDUE_GRANULARITY_BURST ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int DMA_SLAVE_BUSWIDTH_16_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_32_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_64_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_8_BYTES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCAR_DMAC_MEMCPY_XFER_SIZE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 int /*<<< orphan*/ * devm_kcalloc (TYPE_1__*,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct rcar_dmac* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int dma_async_device_register (struct dma_device*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_mask_and_coherent (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 int of_dma_controller_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rcar_dmac*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int pm_runtime_get_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_1__*) ; 
 int /*<<< orphan*/  rcar_dmac_alloc_chan_resources ; 
 int /*<<< orphan*/  rcar_dmac_chan_pause ; 
 int rcar_dmac_chan_probe (struct rcar_dmac*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  rcar_dmac_chan_terminate_all ; 
 int /*<<< orphan*/  rcar_dmac_device_config ; 
 int /*<<< orphan*/  rcar_dmac_device_synchronize ; 
 int /*<<< orphan*/  rcar_dmac_free_chan_resources ; 
 int rcar_dmac_init (struct rcar_dmac*) ; 
 int /*<<< orphan*/  rcar_dmac_issue_pending ; 
 int /*<<< orphan*/  rcar_dmac_of_xlate ; 
 int rcar_dmac_parse_of (TYPE_1__*,struct rcar_dmac*) ; 
 int /*<<< orphan*/  rcar_dmac_prep_dma_cyclic ; 
 int /*<<< orphan*/  rcar_dmac_prep_dma_memcpy ; 
 int /*<<< orphan*/  rcar_dmac_prep_slave_sg ; 
 int /*<<< orphan*/  rcar_dmac_tx_status ; 

__attribute__((used)) static int rcar_dmac_probe(struct platform_device *pdev)
{
	const enum dma_slave_buswidth widths = DMA_SLAVE_BUSWIDTH_1_BYTE |
		DMA_SLAVE_BUSWIDTH_2_BYTES | DMA_SLAVE_BUSWIDTH_4_BYTES |
		DMA_SLAVE_BUSWIDTH_8_BYTES | DMA_SLAVE_BUSWIDTH_16_BYTES |
		DMA_SLAVE_BUSWIDTH_32_BYTES | DMA_SLAVE_BUSWIDTH_64_BYTES;
	unsigned int channels_offset = 0;
	struct dma_device *engine;
	struct rcar_dmac *dmac;
	struct resource *mem;
	unsigned int i;
	int ret;

	dmac = devm_kzalloc(&pdev->dev, sizeof(*dmac), GFP_KERNEL);
	if (!dmac)
		return -ENOMEM;

	dmac->dev = &pdev->dev;
	platform_set_drvdata(pdev, dmac);
	dma_set_mask_and_coherent(dmac->dev, DMA_BIT_MASK(40));

	ret = rcar_dmac_parse_of(&pdev->dev, dmac);
	if (ret < 0)
		return ret;

	/*
	 * A still unconfirmed hardware bug prevents the IPMMU microTLB 0 to be
	 * flushed correctly, resulting in memory corruption. DMAC 0 channel 0
	 * is connected to microTLB 0 on currently supported platforms, so we
	 * can't use it with the IPMMU. As the IOMMU API operates at the device
	 * level we can't disable it selectively, so ignore channel 0 for now if
	 * the device is part of an IOMMU group.
	 */
	if (pdev->dev.iommu_group) {
		dmac->n_channels--;
		channels_offset = 1;
	}

	dmac->channels = devm_kcalloc(&pdev->dev, dmac->n_channels,
				      sizeof(*dmac->channels), GFP_KERNEL);
	if (!dmac->channels)
		return -ENOMEM;

	/* Request resources. */
	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dmac->iomem = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(dmac->iomem))
		return PTR_ERR(dmac->iomem);

	/* Enable runtime PM and initialize the device. */
	pm_runtime_enable(&pdev->dev);
	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "runtime PM get sync failed (%d)\n", ret);
		return ret;
	}

	ret = rcar_dmac_init(dmac);
	pm_runtime_put(&pdev->dev);

	if (ret) {
		dev_err(&pdev->dev, "failed to reset device\n");
		goto error;
	}

	/* Initialize engine */
	engine = &dmac->engine;

	dma_cap_set(DMA_MEMCPY, engine->cap_mask);
	dma_cap_set(DMA_SLAVE, engine->cap_mask);

	engine->dev		= &pdev->dev;
	engine->copy_align	= ilog2(RCAR_DMAC_MEMCPY_XFER_SIZE);

	engine->src_addr_widths	= widths;
	engine->dst_addr_widths	= widths;
	engine->directions	= BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	engine->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

	engine->device_alloc_chan_resources	= rcar_dmac_alloc_chan_resources;
	engine->device_free_chan_resources	= rcar_dmac_free_chan_resources;
	engine->device_prep_dma_memcpy		= rcar_dmac_prep_dma_memcpy;
	engine->device_prep_slave_sg		= rcar_dmac_prep_slave_sg;
	engine->device_prep_dma_cyclic		= rcar_dmac_prep_dma_cyclic;
	engine->device_config			= rcar_dmac_device_config;
	engine->device_pause			= rcar_dmac_chan_pause;
	engine->device_terminate_all		= rcar_dmac_chan_terminate_all;
	engine->device_tx_status		= rcar_dmac_tx_status;
	engine->device_issue_pending		= rcar_dmac_issue_pending;
	engine->device_synchronize		= rcar_dmac_device_synchronize;

	INIT_LIST_HEAD(&engine->channels);

	for (i = 0; i < dmac->n_channels; ++i) {
		ret = rcar_dmac_chan_probe(dmac, &dmac->channels[i],
					   i + channels_offset);
		if (ret < 0)
			goto error;
	}

	/* Register the DMAC as a DMA provider for DT. */
	ret = of_dma_controller_register(pdev->dev.of_node, rcar_dmac_of_xlate,
					 NULL);
	if (ret < 0)
		goto error;

	/*
	 * Register the DMA engine device.
	 *
	 * Default transfer size of 32 bytes requires 32-byte alignment.
	 */
	ret = dma_async_device_register(engine);
	if (ret < 0)
		goto error;

	return 0;

error:
	of_dma_controller_free(pdev->dev.of_node);
	pm_runtime_disable(&pdev->dev);
	return ret;
}