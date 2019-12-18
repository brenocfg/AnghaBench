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
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lan743x_hardware_cleanup (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_netdev_close (struct net_device*) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void lan743x_pcidev_shutdown(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct lan743x_adapter *adapter = netdev_priv(netdev);

	rtnl_lock();
	netif_device_detach(netdev);

	/* close netdev when netdev is at running state.
	 * For instance, it is true when system goes to sleep by pm-suspend
	 * However, it is false when system goes to sleep by suspend GUI menu
	 */
	if (netif_running(netdev))
		lan743x_netdev_close(netdev);
	rtnl_unlock();

#ifdef CONFIG_PM
	pci_save_state(pdev);
#endif

	/* clean up lan743x portion */
	lan743x_hardware_cleanup(adapter);
}