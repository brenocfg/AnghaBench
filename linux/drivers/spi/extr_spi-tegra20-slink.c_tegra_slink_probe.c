#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct tegra_slink_data {int irq; int max_buf_size; int dma_buf_size; int /*<<< orphan*/  clk; int /*<<< orphan*/  def_command2_reg; int /*<<< orphan*/  def_command_reg; int /*<<< orphan*/  xfer_completion; int /*<<< orphan*/  rx_dma_complete; int /*<<< orphan*/  tx_dma_complete; int /*<<< orphan*/  rst; int /*<<< orphan*/  base; int /*<<< orphan*/  phys; TYPE_2__* dev; int /*<<< orphan*/  lock; struct tegra_slink_chip_data const* chip_data; struct spi_master* master; } ;
struct tegra_slink_chip_data {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int mode_bits; int auto_runtime_pm; int max_speed_hz; TYPE_1__ dev; int /*<<< orphan*/  num_chipselect; int /*<<< orphan*/  unprepare_message; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  setup; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_19__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {struct tegra_slink_chip_data* data; } ;

/* Variables and functions */
 int DEFAULT_SPI_DMA_BUF_LEN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_CHIP_SELECT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLINK_COMMAND ; 
 int /*<<< orphan*/  SLINK_COMMAND2 ; 
 int /*<<< orphan*/  SLINK_CS_ACTIVE_BETWEEN ; 
 int SLINK_FIFO_DEPTH ; 
 int /*<<< orphan*/  SLINK_M_S ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int /*<<< orphan*/  devm_reset_control_get_exclusive (TYPE_2__*,char*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int /*<<< orphan*/  free_irq (int,struct tegra_slink_data*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (TYPE_2__*) ; 
 int pm_runtime_get_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (TYPE_2__*) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_slink_data*) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct tegra_slink_data* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_slink_deinit_dma_param (struct tegra_slink_data*,int) ; 
 int tegra_slink_init_dma_param (struct tegra_slink_data*,int) ; 
 int /*<<< orphan*/  tegra_slink_isr ; 
 int /*<<< orphan*/  tegra_slink_isr_thread ; 
 int /*<<< orphan*/  tegra_slink_of_match ; 
 int /*<<< orphan*/  tegra_slink_prepare_message ; 
 int tegra_slink_runtime_resume (TYPE_2__*) ; 
 int /*<<< orphan*/  tegra_slink_runtime_suspend (TYPE_2__*) ; 
 int /*<<< orphan*/  tegra_slink_setup ; 
 int /*<<< orphan*/  tegra_slink_transfer_one ; 
 int /*<<< orphan*/  tegra_slink_unprepare_message ; 
 int /*<<< orphan*/  tegra_slink_writel (struct tegra_slink_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_slink_probe(struct platform_device *pdev)
{
	struct spi_master	*master;
	struct tegra_slink_data	*tspi;
	struct resource		*r;
	int ret, spi_irq;
	const struct tegra_slink_chip_data *cdata = NULL;
	const struct of_device_id *match;

	match = of_match_device(tegra_slink_of_match, &pdev->dev);
	if (!match) {
		dev_err(&pdev->dev, "Error: No device match found\n");
		return -ENODEV;
	}
	cdata = match->data;

	master = spi_alloc_master(&pdev->dev, sizeof(*tspi));
	if (!master) {
		dev_err(&pdev->dev, "master allocation failed\n");
		return -ENOMEM;
	}

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->setup = tegra_slink_setup;
	master->prepare_message = tegra_slink_prepare_message;
	master->transfer_one = tegra_slink_transfer_one;
	master->unprepare_message = tegra_slink_unprepare_message;
	master->auto_runtime_pm = true;
	master->num_chipselect = MAX_CHIP_SELECT;

	platform_set_drvdata(pdev, master);
	tspi = spi_master_get_devdata(master);
	tspi->master = master;
	tspi->dev = &pdev->dev;
	tspi->chip_data = cdata;
	spin_lock_init(&tspi->lock);

	if (of_property_read_u32(tspi->dev->of_node, "spi-max-frequency",
				 &master->max_speed_hz))
		master->max_speed_hz = 25000000; /* 25MHz */

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r) {
		dev_err(&pdev->dev, "No IO memory resource\n");
		ret = -ENODEV;
		goto exit_free_master;
	}
	tspi->phys = r->start;
	tspi->base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(tspi->base)) {
		ret = PTR_ERR(tspi->base);
		goto exit_free_master;
	}

	/* disabled clock may cause interrupt storm upon request */
	tspi->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(tspi->clk)) {
		ret = PTR_ERR(tspi->clk);
		dev_err(&pdev->dev, "Can not get clock %d\n", ret);
		goto exit_free_master;
	}
	ret = clk_prepare(tspi->clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "Clock prepare failed %d\n", ret);
		goto exit_free_master;
	}
	ret = clk_enable(tspi->clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "Clock enable failed %d\n", ret);
		goto exit_free_master;
	}

	spi_irq = platform_get_irq(pdev, 0);
	tspi->irq = spi_irq;
	ret = request_threaded_irq(tspi->irq, tegra_slink_isr,
			tegra_slink_isr_thread, IRQF_ONESHOT,
			dev_name(&pdev->dev), tspi);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register ISR for IRQ %d\n",
					tspi->irq);
		goto exit_clk_disable;
	}

	tspi->rst = devm_reset_control_get_exclusive(&pdev->dev, "spi");
	if (IS_ERR(tspi->rst)) {
		dev_err(&pdev->dev, "can not get reset\n");
		ret = PTR_ERR(tspi->rst);
		goto exit_free_irq;
	}

	tspi->max_buf_size = SLINK_FIFO_DEPTH << 2;
	tspi->dma_buf_size = DEFAULT_SPI_DMA_BUF_LEN;

	ret = tegra_slink_init_dma_param(tspi, true);
	if (ret < 0)
		goto exit_free_irq;
	ret = tegra_slink_init_dma_param(tspi, false);
	if (ret < 0)
		goto exit_rx_dma_free;
	tspi->max_buf_size = tspi->dma_buf_size;
	init_completion(&tspi->tx_dma_complete);
	init_completion(&tspi->rx_dma_complete);

	init_completion(&tspi->xfer_completion);

	pm_runtime_enable(&pdev->dev);
	if (!pm_runtime_enabled(&pdev->dev)) {
		ret = tegra_slink_runtime_resume(&pdev->dev);
		if (ret)
			goto exit_pm_disable;
	}

	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "pm runtime get failed, e = %d\n", ret);
		goto exit_pm_disable;
	}
	tspi->def_command_reg  = SLINK_M_S;
	tspi->def_command2_reg = SLINK_CS_ACTIVE_BETWEEN;
	tegra_slink_writel(tspi, tspi->def_command_reg, SLINK_COMMAND);
	tegra_slink_writel(tspi, tspi->def_command2_reg, SLINK_COMMAND2);
	pm_runtime_put(&pdev->dev);

	master->dev.of_node = pdev->dev.of_node;
	ret = devm_spi_register_master(&pdev->dev, master);
	if (ret < 0) {
		dev_err(&pdev->dev, "can not register to master err %d\n", ret);
		goto exit_pm_disable;
	}
	return ret;

exit_pm_disable:
	pm_runtime_disable(&pdev->dev);
	if (!pm_runtime_status_suspended(&pdev->dev))
		tegra_slink_runtime_suspend(&pdev->dev);
	tegra_slink_deinit_dma_param(tspi, false);
exit_rx_dma_free:
	tegra_slink_deinit_dma_param(tspi, true);
exit_free_irq:
	free_irq(spi_irq, tspi);
exit_clk_disable:
	clk_disable(tspi->clk);
exit_free_master:
	spi_master_put(master);
	return ret;
}