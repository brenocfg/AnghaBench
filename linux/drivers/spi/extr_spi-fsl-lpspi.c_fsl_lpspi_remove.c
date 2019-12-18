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
struct fsl_lpspi_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct spi_controller* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 struct fsl_lpspi_data* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_controller*) ; 

__attribute__((used)) static int fsl_lpspi_remove(struct platform_device *pdev)
{
	struct spi_controller *controller = platform_get_drvdata(pdev);
	struct fsl_lpspi_data *fsl_lpspi =
				spi_controller_get_devdata(controller);

	pm_runtime_disable(fsl_lpspi->dev);

	spi_master_put(controller);

	return 0;
}