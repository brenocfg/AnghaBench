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
struct ssp_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct driver_data {TYPE_1__* controller_info; struct ssp_device* ssp; } ;
struct TYPE_2__ {scalar_t__ enable_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSCR0 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct driver_data*) ; 
 struct driver_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pxa2xx_spi_dma_release (struct driver_data*) ; 
 int /*<<< orphan*/  pxa2xx_spi_write (struct driver_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa_ssp_free (struct ssp_device*) ; 

__attribute__((used)) static int pxa2xx_spi_remove(struct platform_device *pdev)
{
	struct driver_data *drv_data = platform_get_drvdata(pdev);
	struct ssp_device *ssp;

	if (!drv_data)
		return 0;
	ssp = drv_data->ssp;

	pm_runtime_get_sync(&pdev->dev);

	/* Disable the SSP at the peripheral and SOC level */
	pxa2xx_spi_write(drv_data, SSCR0, 0);
	clk_disable_unprepare(ssp->clk);

	/* Release DMA */
	if (drv_data->controller_info->enable_dma)
		pxa2xx_spi_dma_release(drv_data);

	pm_runtime_put_noidle(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	/* Release IRQ */
	free_irq(ssp->irq, drv_data);

	/* Release SSP */
	pxa_ssp_free(ssp);

	return 0;
}