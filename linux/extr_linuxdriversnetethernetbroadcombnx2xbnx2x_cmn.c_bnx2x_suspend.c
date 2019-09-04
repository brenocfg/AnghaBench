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
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  UNLOAD_CLOSE ; 
 int /*<<< orphan*/  bnx2x_nic_unload (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_set_power_state (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pci_choose_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int bnx2x_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct bnx2x *bp;

	if (!dev) {
		dev_err(&pdev->dev, "BAD net device from bnx2x_init_one\n");
		return -ENODEV;
	}
	bp = netdev_priv(dev);

	rtnl_lock();

	pci_save_state(pdev);

	if (!netif_running(dev)) {
		rtnl_unlock();
		return 0;
	}

	netif_device_detach(dev);

	bnx2x_nic_unload(bp, UNLOAD_CLOSE, false);

	bnx2x_set_power_state(bp, pci_choose_state(pdev, state));

	rtnl_unlock();

	return 0;
}