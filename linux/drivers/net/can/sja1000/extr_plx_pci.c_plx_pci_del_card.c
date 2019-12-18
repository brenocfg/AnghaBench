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
struct sja1000_priv {scalar_t__ reg_base; } ;
struct plx_pci_card {scalar_t__ conf_addr; int /*<<< orphan*/  (* reset_func ) (struct pci_dev*) ;struct net_device** net_dev; } ;
struct pci_dev {scalar_t__ device; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ MARATHON_PCIE_DEVICE_ID ; 
 scalar_t__ PCI_DEVICE_ID_PLX_9056 ; 
 scalar_t__ PLX9056_INTCSR ; 
 scalar_t__ PLX_INTCSR ; 
 int PLX_PCI_MAX_CHAN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_sja1000dev (struct net_device*) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct plx_pci_card*) ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct plx_pci_card* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_sja1000dev (struct net_device*) ; 

__attribute__((used)) static void plx_pci_del_card(struct pci_dev *pdev)
{
	struct plx_pci_card *card = pci_get_drvdata(pdev);
	struct net_device *dev;
	struct sja1000_priv *priv;
	int i = 0;

	for (i = 0; i < PLX_PCI_MAX_CHAN; i++) {
		dev = card->net_dev[i];
		if (!dev)
			continue;

		dev_info(&pdev->dev, "Removing %s\n", dev->name);
		unregister_sja1000dev(dev);
		priv = netdev_priv(dev);
		if (priv->reg_base)
			pci_iounmap(pdev, priv->reg_base);
		free_sja1000dev(dev);
	}

	card->reset_func(pdev);

	/*
	 * Disable interrupts from PCI-card and disable local
	 * interrupts
	 */
	if (pdev->device != PCI_DEVICE_ID_PLX_9056 &&
	    pdev->device != MARATHON_PCIE_DEVICE_ID)
		iowrite32(0x0, card->conf_addr + PLX_INTCSR);
	else
		iowrite32(0x0, card->conf_addr + PLX9056_INTCSR);

	if (card->conf_addr)
		pci_iounmap(pdev, card->conf_addr);

	kfree(card);

	pci_disable_device(pdev);
}