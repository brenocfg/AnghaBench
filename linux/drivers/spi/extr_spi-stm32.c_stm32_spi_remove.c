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
struct stm32_spi {int /*<<< orphan*/  clk; TYPE_1__* cfg; } ;
struct spi_master {scalar_t__ dma_rx; scalar_t__ dma_tx; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct stm32_spi*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 struct stm32_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  stub1 (struct stm32_spi*) ; 

__attribute__((used)) static int stm32_spi_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct stm32_spi *spi = spi_master_get_devdata(master);

	spi->cfg->disable(spi);

	if (master->dma_tx)
		dma_release_channel(master->dma_tx);
	if (master->dma_rx)
		dma_release_channel(master->dma_rx);

	clk_disable_unprepare(spi->clk);

	pm_runtime_disable(&pdev->dev);

	return 0;
}