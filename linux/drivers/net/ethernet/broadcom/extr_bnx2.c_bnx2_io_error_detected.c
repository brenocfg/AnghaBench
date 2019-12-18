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
struct bnx2 {int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_DRV_MSG_CODE_RESET ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  bnx2_netif_stop (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_reset_nic (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static pci_ers_result_t bnx2_io_error_detected(struct pci_dev *pdev,
					       pci_channel_state_t state)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct bnx2 *bp = netdev_priv(dev);

	rtnl_lock();
	netif_device_detach(dev);

	if (state == pci_channel_io_perm_failure) {
		rtnl_unlock();
		return PCI_ERS_RESULT_DISCONNECT;
	}

	if (netif_running(dev)) {
		bnx2_netif_stop(bp, true);
		del_timer_sync(&bp->timer);
		bnx2_reset_nic(bp, BNX2_DRV_MSG_CODE_RESET);
	}

	pci_disable_device(pdev);
	rtnl_unlock();

	/* Request a slot slot reset. */
	return PCI_ERS_RESULT_NEED_RESET;
}