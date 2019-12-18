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
struct synquacer_spi {int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; } ;
struct spi_master {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 struct synquacer_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int synquacer_spi_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct synquacer_spi *sspi = spi_master_get_devdata(master);

	pm_runtime_disable(sspi->dev);

	clk_disable_unprepare(sspi->clk);

	return 0;
}