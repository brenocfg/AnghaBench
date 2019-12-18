#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ti_qspi {int spi_max_frequency; int mmap_enabled; int /*<<< orphan*/ * mmap_base; int /*<<< orphan*/ * rx_chan; scalar_t__ mmap_phys_base; int /*<<< orphan*/  transfer_complete; TYPE_2__* dev; int /*<<< orphan*/  rx_bb_addr; int /*<<< orphan*/  rx_bb_dma_addr; int /*<<< orphan*/ * fclk; int /*<<< orphan*/  ctrl_reg; int /*<<< orphan*/ * ctrl_base; int /*<<< orphan*/ * base; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  mmap_size; struct spi_master* master; } ;
struct TYPE_13__ {struct device_node* of_node; } ;
struct spi_master {int mode_bits; int auto_runtime_pm; int bits_per_word_mask; int num_chipselect; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * dma_rx; TYPE_1__ dev; int /*<<< orphan*/  transfer_one_message; int /*<<< orphan*/  setup; int /*<<< orphan*/  flags; } ;
struct resource {scalar_t__ start; } ;
struct TYPE_14__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QSPI_AUTOSUSPEND_TIMEOUT ; 
 int /*<<< orphan*/  QSPI_DMA_BUFFER_SIZE ; 
 int SPI_BPW_MASK (int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int /*<<< orphan*/  SPI_MASTER_HALF_DUPLEX ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/ * devm_clk_get (TYPE_2__*,char*) ; 
 void* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dma_request_chan_by_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ti_qspi*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct ti_qspi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/ * syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 
 int /*<<< orphan*/  ti_qspi_mem_ops ; 
 int /*<<< orphan*/  ti_qspi_setup ; 
 int /*<<< orphan*/  ti_qspi_start_transfer_one ; 

__attribute__((used)) static int ti_qspi_probe(struct platform_device *pdev)
{
	struct  ti_qspi *qspi;
	struct spi_master *master;
	struct resource         *r, *res_mmap;
	struct device_node *np = pdev->dev.of_node;
	u32 max_freq;
	int ret = 0, num_cs, irq;
	dma_cap_mask_t mask;

	master = spi_alloc_master(&pdev->dev, sizeof(*qspi));
	if (!master)
		return -ENOMEM;

	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_RX_DUAL | SPI_RX_QUAD;

	master->flags = SPI_MASTER_HALF_DUPLEX;
	master->setup = ti_qspi_setup;
	master->auto_runtime_pm = true;
	master->transfer_one_message = ti_qspi_start_transfer_one;
	master->dev.of_node = pdev->dev.of_node;
	master->bits_per_word_mask = SPI_BPW_MASK(32) | SPI_BPW_MASK(16) |
				     SPI_BPW_MASK(8);
	master->mem_ops = &ti_qspi_mem_ops;

	if (!of_property_read_u32(np, "num-cs", &num_cs))
		master->num_chipselect = num_cs;

	qspi = spi_master_get_devdata(master);
	qspi->master = master;
	qspi->dev = &pdev->dev;
	platform_set_drvdata(pdev, qspi);

	r = platform_get_resource_byname(pdev, IORESOURCE_MEM, "qspi_base");
	if (r == NULL) {
		r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
		if (r == NULL) {
			dev_err(&pdev->dev, "missing platform data\n");
			ret = -ENODEV;
			goto free_master;
		}
	}

	res_mmap = platform_get_resource_byname(pdev,
			IORESOURCE_MEM, "qspi_mmap");
	if (res_mmap == NULL) {
		res_mmap = platform_get_resource(pdev, IORESOURCE_MEM, 1);
		if (res_mmap == NULL) {
			dev_err(&pdev->dev,
				"memory mapped resource not required\n");
		}
	}

	if (res_mmap)
		qspi->mmap_size = resource_size(res_mmap);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = irq;
		goto free_master;
	}

	mutex_init(&qspi->list_lock);

	qspi->base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(qspi->base)) {
		ret = PTR_ERR(qspi->base);
		goto free_master;
	}


	if (of_property_read_bool(np, "syscon-chipselects")) {
		qspi->ctrl_base =
		syscon_regmap_lookup_by_phandle(np,
						"syscon-chipselects");
		if (IS_ERR(qspi->ctrl_base)) {
			ret = PTR_ERR(qspi->ctrl_base);
			goto free_master;
		}
		ret = of_property_read_u32_index(np,
						 "syscon-chipselects",
						 1, &qspi->ctrl_reg);
		if (ret) {
			dev_err(&pdev->dev,
				"couldn't get ctrl_mod reg index\n");
			goto free_master;
		}
	}

	qspi->fclk = devm_clk_get(&pdev->dev, "fck");
	if (IS_ERR(qspi->fclk)) {
		ret = PTR_ERR(qspi->fclk);
		dev_err(&pdev->dev, "could not get clk: %d\n", ret);
	}

	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_set_autosuspend_delay(&pdev->dev, QSPI_AUTOSUSPEND_TIMEOUT);
	pm_runtime_enable(&pdev->dev);

	if (!of_property_read_u32(np, "spi-max-frequency", &max_freq))
		qspi->spi_max_frequency = max_freq;

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	qspi->rx_chan = dma_request_chan_by_mask(&mask);
	if (IS_ERR(qspi->rx_chan)) {
		dev_err(qspi->dev,
			"No Rx DMA available, trying mmap mode\n");
		qspi->rx_chan = NULL;
		ret = 0;
		goto no_dma;
	}
	qspi->rx_bb_addr = dma_alloc_coherent(qspi->dev,
					      QSPI_DMA_BUFFER_SIZE,
					      &qspi->rx_bb_dma_addr,
					      GFP_KERNEL | GFP_DMA);
	if (!qspi->rx_bb_addr) {
		dev_err(qspi->dev,
			"dma_alloc_coherent failed, using PIO mode\n");
		dma_release_channel(qspi->rx_chan);
		goto no_dma;
	}
	master->dma_rx = qspi->rx_chan;
	init_completion(&qspi->transfer_complete);
	if (res_mmap)
		qspi->mmap_phys_base = (dma_addr_t)res_mmap->start;

no_dma:
	if (!qspi->rx_chan && res_mmap) {
		qspi->mmap_base = devm_ioremap_resource(&pdev->dev, res_mmap);
		if (IS_ERR(qspi->mmap_base)) {
			dev_info(&pdev->dev,
				 "mmap failed with error %ld using PIO mode\n",
				 PTR_ERR(qspi->mmap_base));
			qspi->mmap_base = NULL;
			master->mem_ops = NULL;
		}
	}
	qspi->mmap_enabled = false;

	ret = devm_spi_register_master(&pdev->dev, master);
	if (!ret)
		return 0;

	pm_runtime_disable(&pdev->dev);
free_master:
	spi_master_put(master);
	return ret;
}