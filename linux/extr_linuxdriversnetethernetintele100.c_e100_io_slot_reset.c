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
struct pci_dev {int /*<<< orphan*/  devfn; } ;
struct nic {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e100_hw_reset (struct nic*) ; 
 int /*<<< orphan*/  e100_phy_init (struct nic*) ; 
 struct nic* netdev_priv (struct net_device*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static pci_ers_result_t e100_io_slot_reset(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct nic *nic = netdev_priv(netdev);

	if (pci_enable_device(pdev)) {
		pr_err("Cannot re-enable PCI device after reset\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}
	pci_set_master(pdev);

	/* Only one device per card can do a reset */
	if (0 != PCI_FUNC(pdev->devfn))
		return PCI_ERS_RESULT_RECOVERED;
	e100_hw_reset(nic);
	e100_phy_init(nic);

	return PCI_ERS_RESULT_RECOVERED;
}