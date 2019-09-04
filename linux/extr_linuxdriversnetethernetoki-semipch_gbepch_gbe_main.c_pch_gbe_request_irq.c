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
struct pch_gbe_adapter {int /*<<< orphan*/  pdev; int /*<<< orphan*/  irq; struct net_device* netdev; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  PCI_IRQ_ALL_TYPES ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  pch_gbe_intr ; 
 int pci_alloc_irq_vectors (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_msi_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int pch_gbe_request_irq(struct pch_gbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int err;

	err = pci_alloc_irq_vectors(adapter->pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	if (err < 0)
		return err;

	adapter->irq = pci_irq_vector(adapter->pdev, 0);

	err = request_irq(adapter->irq, &pch_gbe_intr, IRQF_SHARED,
			  netdev->name, netdev);
	if (err)
		netdev_err(netdev, "Unable to allocate interrupt Error: %d\n",
			   err);
	netdev_dbg(netdev, "have_msi : %d  return : 0x%04x\n",
		   pci_dev_msi_enabled(adapter->pdev), err);
	return err;
}