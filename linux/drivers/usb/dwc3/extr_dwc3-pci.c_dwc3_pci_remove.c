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
struct pci_dev {scalar_t__ device; int /*<<< orphan*/  dev; } ;
struct dwc3_pci {int /*<<< orphan*/  dwc3; int /*<<< orphan*/  wakeup_work; struct pci_dev* pci; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_INTEL_BYT ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gpiod_remove_lookup_table (int /*<<< orphan*/ *) ; 
 struct dwc3_pci* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  platform_bytcr_gpios ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwc3_pci_remove(struct pci_dev *pci)
{
	struct dwc3_pci		*dwc = pci_get_drvdata(pci);
	struct pci_dev		*pdev = dwc->pci;

	if (pdev->device == PCI_DEVICE_ID_INTEL_BYT)
		gpiod_remove_lookup_table(&platform_bytcr_gpios);
#ifdef CONFIG_PM
	cancel_work_sync(&dwc->wakeup_work);
#endif
	device_init_wakeup(&pci->dev, false);
	pm_runtime_get(&pci->dev);
	platform_device_unregister(dwc->dwc3);
}