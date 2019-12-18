#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct tegra_sflash_data {int irq; int def_command_reg; int /*<<< orphan*/  rst; int /*<<< orphan*/  xfer_completion; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; TYPE_2__* dev; int /*<<< orphan*/  lock; struct spi_master* master; } ;
struct TYPE_17__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int mode_bits; int auto_runtime_pm; int max_speed_hz; TYPE_1__ dev; int /*<<< orphan*/  num_chipselect; int /*<<< orphan*/  transfer_one_message; } ;
struct TYPE_18__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_CHIP_SELECT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_COMMAND ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_SW ; 
 int SPI_M_S ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get_exclusive (TYPE_2__*,char*) ; 
 int devm_spi_register_master (TYPE_2__*,struct spi_master*) ; 
 int /*<<< orphan*/  free_irq (int,struct tegra_sflash_data*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (TYPE_2__*) ; 
 int pm_runtime_get_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (TYPE_2__*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_sflash_data*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 struct spi_master* spi_alloc_master (TYPE_2__*,int) ; 
 struct tegra_sflash_data* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_sflash_isr ; 
 int /*<<< orphan*/  tegra_sflash_of_match ; 
 int tegra_sflash_runtime_resume (TYPE_2__*) ; 
 int /*<<< orphan*/  tegra_sflash_runtime_suspend (TYPE_2__*) ; 
 int /*<<< orphan*/  tegra_sflash_transfer_one_message ; 
 int /*<<< orphan*/  tegra_sflash_writel (struct tegra_sflash_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tegra_sflash_probe(struct platform_device *pdev)
{
	struct spi_master	*master;
	struct tegra_sflash_data	*tsd;
	int ret;
	const struct of_device_id *match;

	match = of_match_device(tegra_sflash_of_match, &pdev->dev);
	if (!match) {
		dev_err(&pdev->dev, "Error: No device match found\n");
		return -ENODEV;
	}

	master = spi_alloc_master(&pdev->dev, sizeof(*tsd));
	if (!master) {
		dev_err(&pdev->dev, "master allocation failed\n");
		return -ENOMEM;
	}

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA;
	master->transfer_one_message = tegra_sflash_transfer_one_message;
	master->auto_runtime_pm = true;
	master->num_chipselect = MAX_CHIP_SELECT;

	platform_set_drvdata(pdev, master);
	tsd = spi_master_get_devdata(master);
	tsd->master = master;
	tsd->dev = &pdev->dev;
	spin_lock_init(&tsd->lock);

	if (of_property_read_u32(tsd->dev->of_node, "spi-max-frequency",
				 &master->max_speed_hz))
		master->max_speed_hz = 25000000; /* 25MHz */

	tsd->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(tsd->base)) {
		ret = PTR_ERR(tsd->base);
		goto exit_free_master;
	}

	tsd->irq = platform_get_irq(pdev, 0);
	ret = request_irq(tsd->irq, tegra_sflash_isr, 0,
			dev_name(&pdev->dev), tsd);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register ISR for IRQ %d\n",
					tsd->irq);
		goto exit_free_master;
	}

	tsd->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(tsd->clk)) {
		dev_err(&pdev->dev, "can not get clock\n");
		ret = PTR_ERR(tsd->clk);
		goto exit_free_irq;
	}

	tsd->rst = devm_reset_control_get_exclusive(&pdev->dev, "spi");
	if (IS_ERR(tsd->rst)) {
		dev_err(&pdev->dev, "can not get reset\n");
		ret = PTR_ERR(tsd->rst);
		goto exit_free_irq;
	}

	init_completion(&tsd->xfer_completion);
	pm_runtime_enable(&pdev->dev);
	if (!pm_runtime_enabled(&pdev->dev)) {
		ret = tegra_sflash_runtime_resume(&pdev->dev);
		if (ret)
			goto exit_pm_disable;
	}

	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "pm runtime get failed, e = %d\n", ret);
		goto exit_pm_disable;
	}

	/* Reset controller */
	reset_control_assert(tsd->rst);
	udelay(2);
	reset_control_deassert(tsd->rst);

	tsd->def_command_reg  = SPI_M_S | SPI_CS_SW;
	tegra_sflash_writel(tsd, tsd->def_command_reg, SPI_COMMAND);
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
		tegra_sflash_runtime_suspend(&pdev->dev);
exit_free_irq:
	free_irq(tsd->irq, tsd);
exit_free_master:
	spi_master_put(master);
	return ret;
}