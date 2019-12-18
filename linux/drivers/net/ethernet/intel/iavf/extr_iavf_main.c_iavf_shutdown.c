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
struct iavf_adapter {scalar_t__ aq_required; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IAVF_REMOVE ; 
 int /*<<< orphan*/  iavf_close (struct net_device*) ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 

__attribute__((used)) static void iavf_shutdown(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct iavf_adapter *adapter = netdev_priv(netdev);

	netif_device_detach(netdev);

	if (netif_running(netdev))
		iavf_close(netdev);

	/* Prevent the watchdog from running. */
	adapter->state = __IAVF_REMOVE;
	adapter->aq_required = 0;

#ifdef CONFIG_PM
	pci_save_state(pdev);

#endif
	pci_disable_device(pdev);
}