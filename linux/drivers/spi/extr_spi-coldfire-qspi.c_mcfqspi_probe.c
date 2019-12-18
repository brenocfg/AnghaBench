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
struct spi_master {int mode_bits; int auto_runtime_pm; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  set_cs; int /*<<< orphan*/  setup; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  num_chipselect; int /*<<< orphan*/  bus_num; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct mcfqspi_platform_data {scalar_t__ cs_control; int /*<<< orphan*/  num_chipselect; int /*<<< orphan*/  bus_num; } ;
struct mcfqspi {scalar_t__ irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  waitq; scalar_t__ cs_control; int /*<<< orphan*/  iobase; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_BPW_RANGE_MASK (int,int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct mcfqspi_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mcfqspi*) ; 
 int devm_spi_register_master (int /*<<< orphan*/ *,struct spi_master*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int mcfqspi_cs_setup (struct mcfqspi*) ; 
 int /*<<< orphan*/  mcfqspi_cs_teardown (struct mcfqspi*) ; 
 int /*<<< orphan*/  mcfqspi_irq_handler ; 
 int /*<<< orphan*/  mcfqspi_set_cs ; 
 int /*<<< orphan*/  mcfqspi_setup ; 
 int /*<<< orphan*/  mcfqspi_transfer_one ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 struct spi_master* spi_alloc_master (int /*<<< orphan*/ *,int) ; 
 struct mcfqspi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int mcfqspi_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct mcfqspi *mcfqspi;
	struct mcfqspi_platform_data *pdata;
	int status;

	pdata = dev_get_platdata(&pdev->dev);
	if (!pdata) {
		dev_dbg(&pdev->dev, "platform data is missing\n");
		return -ENOENT;
	}

	if (!pdata->cs_control) {
		dev_dbg(&pdev->dev, "pdata->cs_control is NULL\n");
		return -EINVAL;
	}

	master = spi_alloc_master(&pdev->dev, sizeof(*mcfqspi));
	if (master == NULL) {
		dev_dbg(&pdev->dev, "spi_alloc_master failed\n");
		return -ENOMEM;
	}

	mcfqspi = spi_master_get_devdata(master);

	mcfqspi->iobase = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(mcfqspi->iobase)) {
		status = PTR_ERR(mcfqspi->iobase);
		goto fail0;
	}

	mcfqspi->irq = platform_get_irq(pdev, 0);
	if (mcfqspi->irq < 0) {
		dev_dbg(&pdev->dev, "platform_get_irq failed\n");
		status = -ENXIO;
		goto fail0;
	}

	status = devm_request_irq(&pdev->dev, mcfqspi->irq, mcfqspi_irq_handler,
				0, pdev->name, mcfqspi);
	if (status) {
		dev_dbg(&pdev->dev, "request_irq failed\n");
		goto fail0;
	}

	mcfqspi->clk = devm_clk_get(&pdev->dev, "qspi_clk");
	if (IS_ERR(mcfqspi->clk)) {
		dev_dbg(&pdev->dev, "clk_get failed\n");
		status = PTR_ERR(mcfqspi->clk);
		goto fail0;
	}
	clk_enable(mcfqspi->clk);

	master->bus_num = pdata->bus_num;
	master->num_chipselect = pdata->num_chipselect;

	mcfqspi->cs_control = pdata->cs_control;
	status = mcfqspi_cs_setup(mcfqspi);
	if (status) {
		dev_dbg(&pdev->dev, "error initializing cs_control\n");
		goto fail1;
	}

	init_waitqueue_head(&mcfqspi->waitq);

	master->mode_bits = SPI_CS_HIGH | SPI_CPOL | SPI_CPHA;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(8, 16);
	master->setup = mcfqspi_setup;
	master->set_cs = mcfqspi_set_cs;
	master->transfer_one = mcfqspi_transfer_one;
	master->auto_runtime_pm = true;

	platform_set_drvdata(pdev, master);
	pm_runtime_enable(&pdev->dev);

	status = devm_spi_register_master(&pdev->dev, master);
	if (status) {
		dev_dbg(&pdev->dev, "spi_register_master failed\n");
		goto fail2;
	}

	dev_info(&pdev->dev, "Coldfire QSPI bus driver\n");

	return 0;

fail2:
	pm_runtime_disable(&pdev->dev);
	mcfqspi_cs_teardown(mcfqspi);
fail1:
	clk_disable(mcfqspi->clk);
fail0:
	spi_master_put(master);

	dev_dbg(&pdev->dev, "Coldfire QSPI probe failed\n");

	return status;
}