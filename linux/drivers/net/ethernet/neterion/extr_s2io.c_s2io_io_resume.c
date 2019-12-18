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
struct s2io_nic {int dummy; } ;
struct pci_dev {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  s2io_card_down (struct s2io_nic*) ; 
 scalar_t__ s2io_card_up (struct s2io_nic*) ; 
 scalar_t__ s2io_set_mac_addr (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s2io_io_resume(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct s2io_nic *sp = netdev_priv(netdev);

	if (netif_running(netdev)) {
		if (s2io_card_up(sp)) {
			pr_err("Can't bring device back up after reset.\n");
			return;
		}

		if (s2io_set_mac_addr(netdev, netdev->dev_addr) == FAILURE) {
			s2io_card_down(sp);
			pr_err("Can't restore mac addr after reset.\n");
			return;
		}
	}

	netif_device_attach(netdev);
	netif_tx_wake_all_queues(netdev);
}