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
struct bnxt {int /*<<< orphan*/  wol; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 scalar_t__ SYSTEM_POWER_OFF ; 
 int /*<<< orphan*/  bnxt_clear_int_mode (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_ulp_shutdown (struct bnxt*) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_wake_from_d3 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 scalar_t__ system_state ; 

__attribute__((used)) static void bnxt_shutdown(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct bnxt *bp;

	if (!dev)
		return;

	rtnl_lock();
	bp = netdev_priv(dev);
	if (!bp)
		goto shutdown_exit;

	if (netif_running(dev))
		dev_close(dev);

	bnxt_ulp_shutdown(bp);

	if (system_state == SYSTEM_POWER_OFF) {
		bnxt_clear_int_mode(bp);
		pci_disable_device(pdev);
		pci_wake_from_d3(pdev, bp->wol);
		pci_set_power_state(pdev, PCI_D3hot);
	}

shutdown_exit:
	rtnl_unlock();
}