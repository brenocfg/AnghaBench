#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {struct net_device* netdev; } ;
typedef  TYPE_1__ MPT_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 TYPE_1__* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void
mptlan_remove(struct pci_dev *pdev)
{
	MPT_ADAPTER 		*ioc = pci_get_drvdata(pdev);
	struct net_device	*dev = ioc->netdev;

	if(dev != NULL) {
		unregister_netdev(dev);
		free_netdev(dev);
	}
}