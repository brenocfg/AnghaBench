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
struct spi_geni_master {int /*<<< orphan*/  irq; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct spi_master*) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 struct spi_geni_master* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_unregister_master (struct spi_master*) ; 

__attribute__((used)) static int spi_geni_remove(struct platform_device *pdev)
{
	struct spi_master *spi = platform_get_drvdata(pdev);
	struct spi_geni_master *mas = spi_master_get_devdata(spi);

	/* Unregister _before_ disabling pm_runtime() so we stop transfers */
	spi_unregister_master(spi);

	free_irq(mas->irq, spi);
	pm_runtime_disable(&pdev->dev);
	return 0;
}