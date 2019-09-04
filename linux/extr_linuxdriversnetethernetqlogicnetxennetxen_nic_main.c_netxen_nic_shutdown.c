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
struct pci_dev {int dummy; } ;
struct netxen_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3cold ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  netxen_nic_detach_func (struct netxen_adapter*) ; 
 scalar_t__ netxen_nic_wol_supported (struct netxen_adapter*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_wake (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 struct netxen_adapter* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ pci_save_state (struct pci_dev*) ; 

__attribute__((used)) static void netxen_nic_shutdown(struct pci_dev *pdev)
{
	struct netxen_adapter *adapter = pci_get_drvdata(pdev);

	netxen_nic_detach_func(adapter);

	if (pci_save_state(pdev))
		return;

	if (netxen_nic_wol_supported(adapter)) {
		pci_enable_wake(pdev, PCI_D3cold, 1);
		pci_enable_wake(pdev, PCI_D3hot, 1);
	}

	pci_disable_device(pdev);
}