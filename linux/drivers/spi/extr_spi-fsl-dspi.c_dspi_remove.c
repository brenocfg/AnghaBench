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
struct spi_controller {int dummy; } ;
struct platform_device {int dummy; } ;
struct fsl_dspi {int /*<<< orphan*/  ctlr; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dspi_release_dma (struct fsl_dspi*) ; 
 struct spi_controller* platform_get_drvdata (struct platform_device*) ; 
 struct fsl_dspi* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_unregister_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dspi_remove(struct platform_device *pdev)
{
	struct spi_controller *ctlr = platform_get_drvdata(pdev);
	struct fsl_dspi *dspi = spi_controller_get_devdata(ctlr);

	/* Disconnect from the SPI framework */
	dspi_release_dma(dspi);
	clk_disable_unprepare(dspi->clk);
	spi_unregister_controller(dspi->ctlr);

	return 0;
}