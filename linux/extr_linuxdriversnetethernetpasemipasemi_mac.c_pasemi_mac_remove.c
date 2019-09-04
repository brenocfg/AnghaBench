#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct pasemi_mac {TYPE_2__* rx; TYPE_1__* tx; int /*<<< orphan*/  iob_pdev; int /*<<< orphan*/  dma_pdev; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  chan; } ;
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct pasemi_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pasemi_dma_free_chan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void pasemi_mac_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct pasemi_mac *mac;

	if (!netdev)
		return;

	mac = netdev_priv(netdev);

	unregister_netdev(netdev);

	pci_disable_device(pdev);
	pci_dev_put(mac->dma_pdev);
	pci_dev_put(mac->iob_pdev);

	pasemi_dma_free_chan(&mac->tx->chan);
	pasemi_dma_free_chan(&mac->rx->chan);

	free_netdev(netdev);
}