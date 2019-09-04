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
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int EIO ; 
 int SKD_MAX_BARS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_choose_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct skd_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skd_release_irq (struct skd_device*) ; 
 int /*<<< orphan*/  skd_stop_device (struct skd_device*) ; 

__attribute__((used)) static int skd_pci_suspend(struct pci_dev *pdev, pm_message_t state)
{
	int i;
	struct skd_device *skdev;

	skdev = pci_get_drvdata(pdev);
	if (!skdev) {
		dev_err(&pdev->dev, "no device data for PCI\n");
		return -EIO;
	}

	skd_stop_device(skdev);

	skd_release_irq(skdev);

	for (i = 0; i < SKD_MAX_BARS; i++)
		if (skdev->mem_map[i])
			iounmap(skdev->mem_map[i]);

	if (skdev->pcie_error_reporting_is_enabled)
		pci_disable_pcie_error_reporting(pdev);

	pci_release_regions(pdev);
	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_set_power_state(pdev, pci_choose_state(pdev, state));
	return 0;
}