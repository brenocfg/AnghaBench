#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int num_chipselect; int mode_bits; int flags; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  set_cs; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  bus_num; TYPE_1__ dev; } ;
struct sifive_spi {int fifo_depth; int cs_inactive; int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; int /*<<< orphan*/  done; } ;
struct TYPE_10__ {int /*<<< orphan*/ * dma_mask; int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SIFIVE_SPI_DEFAULT_DEPTH ; 
 int SIFIVE_SPI_MAX_CS ; 
 int /*<<< orphan*/  SIFIVE_SPI_REG_CSDEF ; 
 int /*<<< orphan*/  SPI_BPW_MASK (int) ; 
 int SPI_CONTROLLER_MUST_TX ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LSB_FIRST ; 
 int SPI_MASTER_GPIO_SS ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int SPI_TX_DUAL ; 
 int SPI_TX_QUAD ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sifive_spi*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 int /*<<< orphan*/  sifive_spi_init (struct sifive_spi*) ; 
 int /*<<< orphan*/  sifive_spi_irq ; 
 int /*<<< orphan*/  sifive_spi_prepare_message ; 
 void* sifive_spi_read (struct sifive_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sifive_spi_set_cs ; 
 int /*<<< orphan*/  sifive_spi_transfer_one ; 
 int /*<<< orphan*/  sifive_spi_write (struct sifive_spi*,int /*<<< orphan*/ ,int) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct sifive_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int sifive_spi_probe(struct platform_device *pdev)
{
	struct sifive_spi *spi;
	int ret, irq, num_cs;
	u32 cs_bits, max_bits_per_word;
	struct spi_master *master;

	master = spi_alloc_master(&pdev->dev, sizeof(struct sifive_spi));
	if (!master) {
		dev_err(&pdev->dev, "out of memory\n");
		return -ENOMEM;
	}

	spi = spi_master_get_devdata(master);
	init_completion(&spi->done);
	platform_set_drvdata(pdev, master);

	spi->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(spi->regs)) {
		ret = PTR_ERR(spi->regs);
		goto put_master;
	}

	spi->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(spi->clk)) {
		dev_err(&pdev->dev, "Unable to find bus clock\n");
		ret = PTR_ERR(spi->clk);
		goto put_master;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = irq;
		goto put_master;
	}

	/* Optional parameters */
	ret =
	  of_property_read_u32(pdev->dev.of_node, "sifive,fifo-depth",
			       &spi->fifo_depth);
	if (ret < 0)
		spi->fifo_depth = SIFIVE_SPI_DEFAULT_DEPTH;

	ret =
	  of_property_read_u32(pdev->dev.of_node, "sifive,max-bits-per-word",
			       &max_bits_per_word);

	if (!ret && max_bits_per_word < 8) {
		dev_err(&pdev->dev, "Only 8bit SPI words supported by the driver\n");
		ret = -EINVAL;
		goto put_master;
	}

	/* Spin up the bus clock before hitting registers */
	ret = clk_prepare_enable(spi->clk);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable bus clock\n");
		goto put_master;
	}

	/* probe the number of CS lines */
	spi->cs_inactive = sifive_spi_read(spi, SIFIVE_SPI_REG_CSDEF);
	sifive_spi_write(spi, SIFIVE_SPI_REG_CSDEF, 0xffffffffU);
	cs_bits = sifive_spi_read(spi, SIFIVE_SPI_REG_CSDEF);
	sifive_spi_write(spi, SIFIVE_SPI_REG_CSDEF, spi->cs_inactive);
	if (!cs_bits) {
		dev_err(&pdev->dev, "Could not auto probe CS lines\n");
		ret = -EINVAL;
		goto put_master;
	}

	num_cs = ilog2(cs_bits) + 1;
	if (num_cs > SIFIVE_SPI_MAX_CS) {
		dev_err(&pdev->dev, "Invalid number of spi slaves\n");
		ret = -EINVAL;
		goto put_master;
	}

	/* Define our master */
	master->dev.of_node = pdev->dev.of_node;
	master->bus_num = pdev->id;
	master->num_chipselect = num_cs;
	master->mode_bits = SPI_CPHA | SPI_CPOL
			  | SPI_CS_HIGH | SPI_LSB_FIRST
			  | SPI_TX_DUAL | SPI_TX_QUAD
			  | SPI_RX_DUAL | SPI_RX_QUAD;
	/* TODO: add driver support for bits_per_word < 8
	 * we need to "left-align" the bits (unless SPI_LSB_FIRST)
	 */
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->flags = SPI_CONTROLLER_MUST_TX | SPI_MASTER_GPIO_SS;
	master->prepare_message = sifive_spi_prepare_message;
	master->set_cs = sifive_spi_set_cs;
	master->transfer_one = sifive_spi_transfer_one;

	pdev->dev.dma_mask = NULL;
	/* Configure the SPI master hardware */
	sifive_spi_init(spi);

	/* Register for SPI Interrupt */
	ret = devm_request_irq(&pdev->dev, irq, sifive_spi_irq, 0,
			       dev_name(&pdev->dev), spi);
	if (ret) {
		dev_err(&pdev->dev, "Unable to bind to interrupt\n");
		goto put_master;
	}

	dev_info(&pdev->dev, "mapped; irq=%d, cs=%d\n",
		 irq, master->num_chipselect);

	ret = devm_spi_register_master(&pdev->dev, master);
	if (ret < 0) {
		dev_err(&pdev->dev, "spi_register_master failed\n");
		goto put_master;
	}

	return 0;

put_master:
	spi_master_put(master);

	return ret;
}