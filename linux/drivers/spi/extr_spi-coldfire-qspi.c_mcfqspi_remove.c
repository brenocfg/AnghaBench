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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mcfqspi {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCFQSPI_QMR_MSTR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcfqspi_cs_teardown (struct mcfqspi*) ; 
 int /*<<< orphan*/  mcfqspi_wr_qmr (struct mcfqspi*,int /*<<< orphan*/ ) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 struct mcfqspi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int mcfqspi_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct mcfqspi *mcfqspi = spi_master_get_devdata(master);

	pm_runtime_disable(&pdev->dev);
	/* disable the hardware (set the baud rate to 0) */
	mcfqspi_wr_qmr(mcfqspi, MCFQSPI_QMR_MSTR);

	mcfqspi_cs_teardown(mcfqspi);
	clk_disable(mcfqspi->clk);

	return 0;
}