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
struct pch_gbe_adapter {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ pch_gbe_up (struct pch_gbe_adapter*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void pch_gbe_io_resume(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);

	if (netif_running(netdev)) {
		if (pch_gbe_up(adapter)) {
			netdev_dbg(netdev,
				   "can't bring device back up after reset\n");
			return;
		}
	}
	netif_device_attach(netdev);
}