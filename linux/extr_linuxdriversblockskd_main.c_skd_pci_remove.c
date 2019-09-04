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
struct skd_device {scalar_t__ pcie_error_reporting_is_enabled; scalar_t__* mem_map; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SKD_MAX_BARS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct skd_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skd_destruct (struct skd_device*) ; 
 int /*<<< orphan*/  skd_release_irq (struct skd_device*) ; 
 int /*<<< orphan*/  skd_stop_device (struct skd_device*) ; 

__attribute__((used)) static void skd_pci_remove(struct pci_dev *pdev)
{
	int i;
	struct skd_device *skdev;

	skdev = pci_get_drvdata(pdev);
	if (!skdev) {
		dev_err(&pdev->dev, "no device data for PCI\n");
		return;
	}
	skd_stop_device(skdev);
	skd_release_irq(skdev);

	for (i = 0; i < SKD_MAX_BARS; i++)
		if (skdev->mem_map[i])
			iounmap(skdev->mem_map[i]);

	if (skdev->pcie_error_reporting_is_enabled)
		pci_disable_pcie_error_reporting(pdev);

	skd_destruct(skdev);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);

	return;
}