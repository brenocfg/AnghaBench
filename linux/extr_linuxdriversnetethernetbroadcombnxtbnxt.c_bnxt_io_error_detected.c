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
struct net_device {int dummy; } ;
struct bnxt {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  bnxt_close (struct net_device*) ; 
 int /*<<< orphan*/  bnxt_ulp_stop (struct bnxt*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static pci_ers_result_t bnxt_io_error_detected(struct pci_dev *pdev,
					       pci_channel_state_t state)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct bnxt *bp = netdev_priv(netdev);

	netdev_info(netdev, "PCI I/O error detected\n");

	rtnl_lock();
	netif_device_detach(netdev);

	bnxt_ulp_stop(bp);

	if (state == pci_channel_io_perm_failure) {
		rtnl_unlock();
		return PCI_ERS_RESULT_DISCONNECT;
	}

	if (netif_running(netdev))
		bnxt_close(netdev);

	pci_disable_device(pdev);
	rtnl_unlock();

	/* Request a slot slot reset. */
	return PCI_ERS_RESULT_NEED_RESET;
}