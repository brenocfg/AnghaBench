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
struct atl1c_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ atl1c_up (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct atl1c_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_msg_hw (struct atl1c_adapter*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void atl1c_io_resume(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct atl1c_adapter *adapter = netdev_priv(netdev);

	if (netif_running(netdev)) {
		if (atl1c_up(adapter)) {
			if (netif_msg_hw(adapter))
				dev_err(&pdev->dev,
					"Cannot bring device back up after reset\n");
			return;
		}
	}

	netif_device_attach(netdev);
}