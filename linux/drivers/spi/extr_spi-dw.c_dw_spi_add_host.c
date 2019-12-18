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
struct device {int /*<<< orphan*/  fwnode; int /*<<< orphan*/  of_node; } ;
struct spi_controller {int use_gpio_descriptors; int mode_bits; struct device dev; int /*<<< orphan*/  can_dma; scalar_t__ set_cs; int /*<<< orphan*/  flags; int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  handle_err; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  setup; int /*<<< orphan*/  num_chipselect; int /*<<< orphan*/  bus_num; int /*<<< orphan*/  bits_per_word_mask; } ;
struct dw_spi {int /*<<< orphan*/  irq; TYPE_1__* dma_ops; scalar_t__ dma_inited; scalar_t__ set_cs; int /*<<< orphan*/  max_freq; int /*<<< orphan*/  num_cs; int /*<<< orphan*/  bus_num; scalar_t__ paddr; scalar_t__ dma_addr; int /*<<< orphan*/  type; struct spi_controller* master; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int (* dma_init ) (struct dw_spi*) ;int /*<<< orphan*/  (* dma_exit ) (struct dw_spi*) ;int /*<<< orphan*/  can_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ DW_SPI_DR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  SPI_BPW_RANGE_MASK (int,int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LOOP ; 
 int /*<<< orphan*/  SPI_MASTER_GPIO_SS ; 
 int /*<<< orphan*/  SSI_MOTO_SPI ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int devm_spi_register_controller (struct device*,struct spi_controller*) ; 
 int /*<<< orphan*/  dw_spi_cleanup ; 
 int /*<<< orphan*/  dw_spi_debugfs_init (struct dw_spi*) ; 
 int /*<<< orphan*/  dw_spi_handle_err ; 
 int /*<<< orphan*/  dw_spi_irq ; 
 scalar_t__ dw_spi_set_cs ; 
 int /*<<< orphan*/  dw_spi_setup ; 
 int /*<<< orphan*/  dw_spi_transfer_one ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct spi_controller*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_controller*) ; 
 struct spi_controller* spi_alloc_master (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_controller_put (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_controller_set_devdata (struct spi_controller*,struct dw_spi*) ; 
 int /*<<< orphan*/  spi_enable_chip (struct dw_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_hw_init (struct device*,struct dw_spi*) ; 
 int stub1 (struct dw_spi*) ; 
 int /*<<< orphan*/  stub2 (struct dw_spi*) ; 

int dw_spi_add_host(struct device *dev, struct dw_spi *dws)
{
	struct spi_controller *master;
	int ret;

	BUG_ON(dws == NULL);

	master = spi_alloc_master(dev, 0);
	if (!master)
		return -ENOMEM;

	dws->master = master;
	dws->type = SSI_MOTO_SPI;
	dws->dma_inited = 0;
	dws->dma_addr = (dma_addr_t)(dws->paddr + DW_SPI_DR);

	spi_controller_set_devdata(master, dws);

	ret = request_irq(dws->irq, dw_spi_irq, IRQF_SHARED, dev_name(dev),
			  master);
	if (ret < 0) {
		dev_err(dev, "can not get IRQ\n");
		goto err_free_master;
	}

	master->use_gpio_descriptors = true;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LOOP;
	master->bits_per_word_mask =  SPI_BPW_RANGE_MASK(4, 16);
	master->bus_num = dws->bus_num;
	master->num_chipselect = dws->num_cs;
	master->setup = dw_spi_setup;
	master->cleanup = dw_spi_cleanup;
	master->set_cs = dw_spi_set_cs;
	master->transfer_one = dw_spi_transfer_one;
	master->handle_err = dw_spi_handle_err;
	master->max_speed_hz = dws->max_freq;
	master->dev.of_node = dev->of_node;
	master->dev.fwnode = dev->fwnode;
	master->flags = SPI_MASTER_GPIO_SS;

	if (dws->set_cs)
		master->set_cs = dws->set_cs;

	/* Basic HW init */
	spi_hw_init(dev, dws);

	if (dws->dma_ops && dws->dma_ops->dma_init) {
		ret = dws->dma_ops->dma_init(dws);
		if (ret) {
			dev_warn(dev, "DMA init failed\n");
			dws->dma_inited = 0;
		} else {
			master->can_dma = dws->dma_ops->can_dma;
		}
	}

	ret = devm_spi_register_controller(dev, master);
	if (ret) {
		dev_err(&master->dev, "problem registering spi master\n");
		goto err_dma_exit;
	}

	dw_spi_debugfs_init(dws);
	return 0;

err_dma_exit:
	if (dws->dma_ops && dws->dma_ops->dma_exit)
		dws->dma_ops->dma_exit(dws);
	spi_enable_chip(dws, 0);
	free_irq(dws->irq, master);
err_free_master:
	spi_controller_put(master);
	return ret;
}