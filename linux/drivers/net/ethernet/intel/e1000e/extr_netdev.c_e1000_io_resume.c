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
struct e1000_adapter {int flags; } ;

/* Variables and functions */
 int FLAG_HAS_AMT ; 
 int /*<<< orphan*/  e1000_init_manageability_pt (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_get_hw_control (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_up (struct e1000_adapter*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void e1000_io_resume(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct e1000_adapter *adapter = netdev_priv(netdev);

	e1000_init_manageability_pt(adapter);

	if (netif_running(netdev))
		e1000e_up(adapter);

	netif_device_attach(netdev);

	/* If the controller has AMT, do not set DRV_LOAD until the interface
	 * is up.  For all other cases, let the f/w know that the h/w is now
	 * under the control of the driver.
	 */
	if (!(adapter->flags & FLAG_HAS_AMT))
		e1000e_get_hw_control(adapter);
}