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
struct spi_master {int use_gpio_descriptors; int mode_bits; int max_speed_hz; int min_speed_hz; scalar_t__ num_chipselect; int /*<<< orphan*/  bits_per_word_mask; int /*<<< orphan*/  bus_num; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  unprepare_transfer_hardware; int /*<<< orphan*/  prepare_transfer_hardware; } ;
struct resource {scalar_t__ start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct ep93xx_spi_info {scalar_t__ use_dma; } ;
struct ep93xx_spi {scalar_t__ mmio; scalar_t__ sspdr_phys; scalar_t__ clk; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  SPI_BPW_RANGE_MASK (int,int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 scalar_t__ SSPCR1 ; 
 scalar_t__ SSPDR ; 
 int clk_get_rate (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ep93xx_spi_info* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned long,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct spi_master*) ; 
 int devm_spi_register_master (int /*<<< orphan*/ *,struct spi_master*) ; 
 int /*<<< orphan*/  ep93xx_spi_interrupt ; 
 int /*<<< orphan*/  ep93xx_spi_prepare_hardware ; 
 int /*<<< orphan*/  ep93xx_spi_prepare_message ; 
 int /*<<< orphan*/  ep93xx_spi_release_dma (struct ep93xx_spi*) ; 
 scalar_t__ ep93xx_spi_setup_dma (struct ep93xx_spi*) ; 
 int /*<<< orphan*/  ep93xx_spi_transfer_one ; 
 int /*<<< orphan*/  ep93xx_spi_unprepare_hardware ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 struct spi_master* spi_alloc_master (int /*<<< orphan*/ *,int) ; 
 struct ep93xx_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ep93xx_spi_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct ep93xx_spi_info *info;
	struct ep93xx_spi *espi;
	struct resource *res;
	int irq;
	int error;

	info = dev_get_platdata(&pdev->dev);
	if (!info) {
		dev_err(&pdev->dev, "missing platform data\n");
		return -EINVAL;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return -EBUSY;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "unable to get iomem resource\n");
		return -ENODEV;
	}

	master = spi_alloc_master(&pdev->dev, sizeof(*espi));
	if (!master)
		return -ENOMEM;

	master->use_gpio_descriptors = true;
	master->prepare_transfer_hardware = ep93xx_spi_prepare_hardware;
	master->unprepare_transfer_hardware = ep93xx_spi_unprepare_hardware;
	master->prepare_message = ep93xx_spi_prepare_message;
	master->transfer_one = ep93xx_spi_transfer_one;
	master->bus_num = pdev->id;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 16);
	/*
	 * The SPI core will count the number of GPIO descriptors to figure
	 * out the number of chip selects available on the platform.
	 */
	master->num_chipselect = 0;

	platform_set_drvdata(pdev, master);

	espi = spi_master_get_devdata(master);

	espi->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(espi->clk)) {
		dev_err(&pdev->dev, "unable to get spi clock\n");
		error = PTR_ERR(espi->clk);
		goto fail_release_master;
	}

	/*
	 * Calculate maximum and minimum supported clock rates
	 * for the controller.
	 */
	master->max_speed_hz = clk_get_rate(espi->clk) / 2;
	master->min_speed_hz = clk_get_rate(espi->clk) / (254 * 256);

	espi->sspdr_phys = res->start + SSPDR;

	espi->mmio = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(espi->mmio)) {
		error = PTR_ERR(espi->mmio);
		goto fail_release_master;
	}

	error = devm_request_irq(&pdev->dev, irq, ep93xx_spi_interrupt,
				0, "ep93xx-spi", master);
	if (error) {
		dev_err(&pdev->dev, "failed to request irq\n");
		goto fail_release_master;
	}

	if (info->use_dma && ep93xx_spi_setup_dma(espi))
		dev_warn(&pdev->dev, "DMA setup failed. Falling back to PIO\n");

	/* make sure that the hardware is disabled */
	writel(0, espi->mmio + SSPCR1);

	error = devm_spi_register_master(&pdev->dev, master);
	if (error) {
		dev_err(&pdev->dev, "failed to register SPI master\n");
		goto fail_free_dma;
	}

	dev_info(&pdev->dev, "EP93xx SPI Controller at 0x%08lx irq %d\n",
		 (unsigned long)res->start, irq);

	return 0;

fail_free_dma:
	ep93xx_spi_release_dma(espi);
fail_release_master:
	spi_master_put(master);

	return error;
}