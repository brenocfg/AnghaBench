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
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;
struct pxa2xx_spi_controller {TYPE_1__ ssp; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unregister (int /*<<< orphan*/ ) ; 
 struct pxa2xx_spi_controller* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct platform_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 

__attribute__((used)) static void pxa2xx_spi_pci_remove(struct pci_dev *dev)
{
	struct platform_device *pdev = pci_get_drvdata(dev);
	struct pxa2xx_spi_controller *spi_pdata;

	spi_pdata = dev_get_platdata(&pdev->dev);

	platform_device_unregister(pdev);
	clk_unregister(spi_pdata->ssp.clk);
}