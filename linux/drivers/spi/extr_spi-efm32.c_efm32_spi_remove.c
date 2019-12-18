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
struct spi_master {int dummy; } ;
struct platform_device {int dummy; } ;
struct efm32_spi_ddata {int /*<<< orphan*/  clk; int /*<<< orphan*/  rxirq; int /*<<< orphan*/  txirq; int /*<<< orphan*/  bitbang; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IEN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efm32_spi_write32 (struct efm32_spi_ddata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct efm32_spi_ddata*) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spi_bitbang_stop (int /*<<< orphan*/ *) ; 
 struct efm32_spi_ddata* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int efm32_spi_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct efm32_spi_ddata *ddata = spi_master_get_devdata(master);

	spi_bitbang_stop(&ddata->bitbang);

	efm32_spi_write32(ddata, 0, REG_IEN);

	free_irq(ddata->txirq, ddata);
	free_irq(ddata->rxirq, ddata);
	clk_disable_unprepare(ddata->clk);
	spi_master_put(master);

	return 0;
}