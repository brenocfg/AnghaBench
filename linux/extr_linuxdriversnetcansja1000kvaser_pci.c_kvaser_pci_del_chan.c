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
struct sja1000_priv {int /*<<< orphan*/  reg_base; struct kvaser_pci* priv; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct kvaser_pci {int no_channels; int /*<<< orphan*/  res_addr; TYPE_1__* pci_dev; int /*<<< orphan*/  conf_addr; struct net_device** slave_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_sja1000dev (struct net_device*) ; 
 int /*<<< orphan*/  kvaser_pci_disable_irq (struct net_device*) ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_iounmap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_sja1000dev (struct net_device*) ; 

__attribute__((used)) static void kvaser_pci_del_chan(struct net_device *dev)
{
	struct sja1000_priv *priv;
	struct kvaser_pci *board;
	int i;

	if (!dev)
		return;
	priv = netdev_priv(dev);
	board = priv->priv;
	if (!board)
		return;

	dev_info(&board->pci_dev->dev, "Removing device %s\n",
		 dev->name);

	/* Disable PCI interrupts */
	kvaser_pci_disable_irq(dev);

	for (i = 0; i < board->no_channels - 1; i++) {
		if (board->slave_dev[i]) {
			dev_info(&board->pci_dev->dev, "Removing device %s\n",
				 board->slave_dev[i]->name);
			unregister_sja1000dev(board->slave_dev[i]);
			free_sja1000dev(board->slave_dev[i]);
		}
	}
	unregister_sja1000dev(dev);

	pci_iounmap(board->pci_dev, priv->reg_base);
	pci_iounmap(board->pci_dev, board->conf_addr);
	pci_iounmap(board->pci_dev, board->res_addr);

	free_sja1000dev(dev);
}