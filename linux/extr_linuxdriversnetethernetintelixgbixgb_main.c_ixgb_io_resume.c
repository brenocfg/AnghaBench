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
struct ixgb_adapter {int /*<<< orphan*/  watchdog_timer; } ;

/* Variables and functions */
 scalar_t__ ixgb_up (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void ixgb_io_resume(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct ixgb_adapter *adapter = netdev_priv(netdev);

	pci_set_master(pdev);

	if (netif_running(netdev)) {
		if (ixgb_up(adapter)) {
			pr_err("can't bring device back up after reset\n");
			return;
		}
	}

	netif_device_attach(netdev);
	mod_timer(&adapter->watchdog_timer, jiffies);
}