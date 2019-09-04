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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pci_dev {int dummy; } ;
struct macb_platform_data {int /*<<< orphan*/  hclk; int /*<<< orphan*/  pclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unregister (int /*<<< orphan*/ ) ; 
 struct macb_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct platform_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 

__attribute__((used)) static void macb_remove(struct pci_dev *pdev)
{
	struct platform_device *plat_dev = pci_get_drvdata(pdev);
	struct macb_platform_data *plat_data = dev_get_platdata(&plat_dev->dev);

	platform_device_unregister(plat_dev);
	clk_unregister(plat_data->pclk);
	clk_unregister(plat_data->hclk);
}