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
struct bnx2 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 scalar_t__ SYSTEM_POWER_OFF ; 
 int /*<<< orphan*/  bnx2_set_power_state (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_close (int /*<<< orphan*/ ) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 scalar_t__ system_state ; 

__attribute__((used)) static void bnx2_shutdown(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct bnx2 *bp;

	if (!dev)
		return;

	bp = netdev_priv(dev);
	if (!bp)
		return;

	rtnl_lock();
	if (netif_running(dev))
		dev_close(bp->dev);

	if (system_state == SYSTEM_POWER_OFF)
		bnx2_set_power_state(bp, PCI_D3hot);

	rtnl_unlock();
}