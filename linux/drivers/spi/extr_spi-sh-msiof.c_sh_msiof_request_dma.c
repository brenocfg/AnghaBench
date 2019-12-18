#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_controller {TYPE_2__* dma_tx; TYPE_2__* dma_rx; } ;
struct sh_msiof_spi_priv {void* tx_dma_page; void* rx_dma_page; void* tx_dma_addr; void* rx_dma_addr; struct spi_controller* ctlr; struct sh_msiof_spi_info* info; struct platform_device* pdev; } ;
struct sh_msiof_spi_info {unsigned int dma_tx_id; unsigned int dma_rx_id; } ;
struct resource {scalar_t__ start; } ;
struct device {scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENODEV ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ RFDR ; 
 scalar_t__ TFDR ; 
 scalar_t__ __get_free_page (int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 void* dma_map_single (struct device*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,void*) ; 
 int /*<<< orphan*/  dma_release_channel (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 void* sh_msiof_request_dma_chan (struct device*,int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 

__attribute__((used)) static int sh_msiof_request_dma(struct sh_msiof_spi_priv *p)
{
	struct platform_device *pdev = p->pdev;
	struct device *dev = &pdev->dev;
	const struct sh_msiof_spi_info *info = p->info;
	unsigned int dma_tx_id, dma_rx_id;
	const struct resource *res;
	struct spi_controller *ctlr;
	struct device *tx_dev, *rx_dev;

	if (dev->of_node) {
		/* In the OF case we will get the slave IDs from the DT */
		dma_tx_id = 0;
		dma_rx_id = 0;
	} else if (info && info->dma_tx_id && info->dma_rx_id) {
		dma_tx_id = info->dma_tx_id;
		dma_rx_id = info->dma_rx_id;
	} else {
		/* The driver assumes no error */
		return 0;
	}

	/* The DMA engine uses the second register set, if present */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!res)
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	ctlr = p->ctlr;
	ctlr->dma_tx = sh_msiof_request_dma_chan(dev, DMA_MEM_TO_DEV,
						 dma_tx_id, res->start + TFDR);
	if (!ctlr->dma_tx)
		return -ENODEV;

	ctlr->dma_rx = sh_msiof_request_dma_chan(dev, DMA_DEV_TO_MEM,
						 dma_rx_id, res->start + RFDR);
	if (!ctlr->dma_rx)
		goto free_tx_chan;

	p->tx_dma_page = (void *)__get_free_page(GFP_KERNEL | GFP_DMA);
	if (!p->tx_dma_page)
		goto free_rx_chan;

	p->rx_dma_page = (void *)__get_free_page(GFP_KERNEL | GFP_DMA);
	if (!p->rx_dma_page)
		goto free_tx_page;

	tx_dev = ctlr->dma_tx->device->dev;
	p->tx_dma_addr = dma_map_single(tx_dev, p->tx_dma_page, PAGE_SIZE,
					DMA_TO_DEVICE);
	if (dma_mapping_error(tx_dev, p->tx_dma_addr))
		goto free_rx_page;

	rx_dev = ctlr->dma_rx->device->dev;
	p->rx_dma_addr = dma_map_single(rx_dev, p->rx_dma_page, PAGE_SIZE,
					DMA_FROM_DEVICE);
	if (dma_mapping_error(rx_dev, p->rx_dma_addr))
		goto unmap_tx_page;

	dev_info(dev, "DMA available");
	return 0;

unmap_tx_page:
	dma_unmap_single(tx_dev, p->tx_dma_addr, PAGE_SIZE, DMA_TO_DEVICE);
free_rx_page:
	free_page((unsigned long)p->rx_dma_page);
free_tx_page:
	free_page((unsigned long)p->tx_dma_page);
free_rx_chan:
	dma_release_channel(ctlr->dma_rx);
free_tx_chan:
	dma_release_channel(ctlr->dma_tx);
	ctlr->dma_tx = NULL;
	return -ENODEV;
}