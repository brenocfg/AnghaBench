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
struct __vxge_hw_device {struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct __vxge_hw_device* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ vxge_open (struct net_device*) ; 

__attribute__((used)) static void vxge_io_resume(struct pci_dev *pdev)
{
	struct __vxge_hw_device *hldev = pci_get_drvdata(pdev);
	struct net_device *netdev = hldev->ndev;

	if (netif_running(netdev)) {
		if (vxge_open(netdev)) {
			netdev_err(netdev,
				   "Can't bring device back up after reset\n");
			return;
		}
	}

	netif_device_attach(netdev);
}