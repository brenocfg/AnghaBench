#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_nic {int port_num; scalar_t__ irq_type; int /*<<< orphan*/  regs; TYPE_1__** priv; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device* ndev; } ;

/* Variables and functions */
 scalar_t__ IRQ_MSI ; 
 int /*<<< orphan*/  RET () ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct pci_nic* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  vfree (struct pci_nic*) ; 

__attribute__((used)) static void bdx_remove(struct pci_dev *pdev)
{
	struct pci_nic *nic = pci_get_drvdata(pdev);
	struct net_device *ndev;
	int port;

	for (port = 0; port < nic->port_num; port++) {
		ndev = nic->priv[port]->ndev;
		unregister_netdev(ndev);
		free_netdev(ndev);
	}

	/*bdx_hw_reset_direct(nic->regs); */
#ifdef BDX_MSI
	if (nic->irq_type == IRQ_MSI)
		pci_disable_msi(pdev);
#endif

	iounmap(nic->regs);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	vfree(nic);

	RET();
}