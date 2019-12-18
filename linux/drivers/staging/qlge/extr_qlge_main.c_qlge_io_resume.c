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
struct ql_adapter {int /*<<< orphan*/  timer; int /*<<< orphan*/  ndev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  ifup ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int qlge_open (struct net_device*) ; 

__attribute__((used)) static void qlge_io_resume(struct pci_dev *pdev)
{
	struct net_device *ndev = pci_get_drvdata(pdev);
	struct ql_adapter *qdev = netdev_priv(ndev);
	int err = 0;

	if (netif_running(ndev)) {
		err = qlge_open(ndev);
		if (err) {
			netif_err(qdev, ifup, qdev->ndev,
				  "Device initialization failed after reset.\n");
			return;
		}
	} else {
		netif_err(qdev, ifup, qdev->ndev,
			  "Device was not running prior to EEH.\n");
	}
	mod_timer(&qdev->timer, jiffies + (5*HZ));
	netif_device_attach(ndev);
}