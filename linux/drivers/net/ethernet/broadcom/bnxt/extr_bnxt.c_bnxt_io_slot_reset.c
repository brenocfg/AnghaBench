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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct bnxt {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ pci_ers_result_t ;

/* Variables and functions */
 scalar_t__ PCI_ERS_RESULT_DISCONNECT ; 
 scalar_t__ PCI_ERS_RESULT_RECOVERED ; 
 int bnxt_hwrm_func_reset (struct bnxt*) ; 
 int bnxt_open (struct net_device*) ; 
 int /*<<< orphan*/  bnxt_ulp_start (struct bnxt*) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static pci_ers_result_t bnxt_io_slot_reset(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct bnxt *bp = netdev_priv(netdev);
	int err = 0;
	pci_ers_result_t result = PCI_ERS_RESULT_DISCONNECT;

	netdev_info(bp->dev, "PCI Slot Reset\n");

	rtnl_lock();

	if (pci_enable_device(pdev)) {
		dev_err(&pdev->dev,
			"Cannot re-enable PCI device after reset.\n");
	} else {
		pci_set_master(pdev);

		err = bnxt_hwrm_func_reset(bp);
		if (!err && netif_running(netdev))
			err = bnxt_open(netdev);

		if (!err) {
			result = PCI_ERS_RESULT_RECOVERED;
			bnxt_ulp_start(bp);
		}
	}

	if (result != PCI_ERS_RESULT_RECOVERED && netif_running(netdev))
		dev_close(netdev);

	rtnl_unlock();

	return PCI_ERS_RESULT_RECOVERED;
}