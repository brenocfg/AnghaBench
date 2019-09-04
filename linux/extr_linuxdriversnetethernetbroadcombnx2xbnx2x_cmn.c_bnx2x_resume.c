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
struct bnx2x {scalar_t__ recovery_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 scalar_t__ BNX2X_RECOVERY_DONE ; 
 int EAGAIN ; 
 int ENODEV ; 
 int /*<<< orphan*/  LOAD_OPEN ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int bnx2x_nic_load (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_power_state (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int bnx2x_resume(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct bnx2x *bp;
	int rc;

	if (!dev) {
		dev_err(&pdev->dev, "BAD net device from bnx2x_init_one\n");
		return -ENODEV;
	}
	bp = netdev_priv(dev);

	if (bp->recovery_state != BNX2X_RECOVERY_DONE) {
		BNX2X_ERR("Handling parity error recovery. Try again later\n");
		return -EAGAIN;
	}

	rtnl_lock();

	pci_restore_state(pdev);

	if (!netif_running(dev)) {
		rtnl_unlock();
		return 0;
	}

	bnx2x_set_power_state(bp, PCI_D0);
	netif_device_attach(dev);

	rc = bnx2x_nic_load(bp, LOAD_OPEN);

	rtnl_unlock();

	return rc;
}