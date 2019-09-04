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
struct ql_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  ndev; } ;
struct pci_dev {int /*<<< orphan*/  error_state; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  QL_EEH_FATAL ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ifup ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_channel_io_normal ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 scalar_t__ ql_adapter_reset (struct ql_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static pci_ers_result_t qlge_io_slot_reset(struct pci_dev *pdev)
{
	struct net_device *ndev = pci_get_drvdata(pdev);
	struct ql_adapter *qdev = netdev_priv(ndev);

	pdev->error_state = pci_channel_io_normal;

	pci_restore_state(pdev);
	if (pci_enable_device(pdev)) {
		netif_err(qdev, ifup, qdev->ndev,
			  "Cannot re-enable PCI device after reset.\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}
	pci_set_master(pdev);

	if (ql_adapter_reset(qdev)) {
		netif_err(qdev, drv, qdev->ndev, "reset FAILED!\n");
		set_bit(QL_EEH_FATAL, &qdev->flags);
		return PCI_ERS_RESULT_DISCONNECT;
	}

	return PCI_ERS_RESULT_RECOVERED;
}