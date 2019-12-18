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
typedef  int u_short ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct hp100_private {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HP100_BUS_PCI ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MASTER ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int hp100_probe1 (struct net_device*,int,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct net_device*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int hp100_pci_probe(struct pci_dev *pdev,
			   const struct pci_device_id *ent)
{
	struct net_device *dev;
	int ioaddr;
	u_short pci_command;
	int err;

	if (pci_enable_device(pdev))
		return -ENODEV;

	dev = alloc_etherdev(sizeof(struct hp100_private));
	if (!dev) {
		err = -ENOMEM;
		goto out0;
	}

	SET_NETDEV_DEV(dev, &pdev->dev);

	pci_read_config_word(pdev, PCI_COMMAND, &pci_command);
	if (!(pci_command & PCI_COMMAND_IO)) {
#ifdef HP100_DEBUG
		printk("hp100: %s: PCI I/O Bit has not been set. Setting...\n", dev->name);
#endif
		pci_command |= PCI_COMMAND_IO;
		pci_write_config_word(pdev, PCI_COMMAND, pci_command);
	}

	if (!(pci_command & PCI_COMMAND_MASTER)) {
#ifdef HP100_DEBUG
		printk("hp100: %s: PCI Master Bit has not been set. Setting...\n", dev->name);
#endif
		pci_command |= PCI_COMMAND_MASTER;
		pci_write_config_word(pdev, PCI_COMMAND, pci_command);
	}

	ioaddr = pci_resource_start(pdev, 0);
	err = hp100_probe1(dev, ioaddr, HP100_BUS_PCI, pdev);
	if (err)
		goto out1;

#ifdef HP100_DEBUG
	printk("hp100: %s: PCI adapter found at 0x%x\n", dev->name, ioaddr);
#endif
	pci_set_drvdata(pdev, dev);
	return 0;
 out1:
	free_netdev(dev);
 out0:
	pci_disable_device(pdev);
	return err;
}