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
typedef  scalar_t__ u8 ;
struct tlan_priv {unsigned long dma_storage_dma; int dma_size; TYPE_1__* adapter; scalar_t__ rx_list_dma; scalar_t__ tx_list_dma; struct tlan_list* rx_list; struct tlan_list* tx_list; int /*<<< orphan*/ * dma_storage; int /*<<< orphan*/  pci_dev; } ;
struct tlan_list {int dummy; } ;
struct net_device {char* dev_addr; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int addr_ofs; } ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,int) ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int TLAN_NUM_RX_LISTS ; 
 int TLAN_NUM_TX_LISTS ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (int /*<<< orphan*/ ,int,unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int tlan_ee_read_byte (struct net_device*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  tlan_ethtool_ops ; 
 int /*<<< orphan*/  tlan_netdev_ops ; 

__attribute__((used)) static int tlan_init(struct net_device *dev)
{
	int		dma_size;
	int		err;
	int		i;
	struct tlan_priv	*priv;

	priv = netdev_priv(dev);

	dma_size = (TLAN_NUM_RX_LISTS + TLAN_NUM_TX_LISTS)
		* (sizeof(struct tlan_list));
	priv->dma_storage = pci_alloc_consistent(priv->pci_dev,
						 dma_size,
						 &priv->dma_storage_dma);
	priv->dma_size = dma_size;

	if (priv->dma_storage == NULL) {
		pr_err("Could not allocate lists and buffers for %s\n",
		       dev->name);
		return -ENOMEM;
	}
	priv->rx_list = (struct tlan_list *)
		ALIGN((unsigned long)priv->dma_storage, 8);
	priv->rx_list_dma = ALIGN(priv->dma_storage_dma, 8);
	priv->tx_list = priv->rx_list + TLAN_NUM_RX_LISTS;
	priv->tx_list_dma =
		priv->rx_list_dma + sizeof(struct tlan_list)*TLAN_NUM_RX_LISTS;

	err = 0;
	for (i = 0; i < ETH_ALEN; i++)
		err |= tlan_ee_read_byte(dev,
					 (u8) priv->adapter->addr_ofs + i,
					 (u8 *) &dev->dev_addr[i]);
	if (err) {
		pr_err("%s: Error reading MAC from eeprom: %d\n",
		       dev->name, err);
	}
	/* Olicom OC-2325/OC-2326 have the address byte-swapped */
	if (priv->adapter->addr_ofs == 0xf8) {
		for (i = 0; i < ETH_ALEN; i += 2) {
			char tmp = dev->dev_addr[i];
			dev->dev_addr[i] = dev->dev_addr[i + 1];
			dev->dev_addr[i + 1] = tmp;
		}
	}

	netif_carrier_off(dev);

	/* Device methods */
	dev->netdev_ops = &tlan_netdev_ops;
	dev->ethtool_ops = &tlan_ethtool_ops;
	dev->watchdog_timeo = TX_TIMEOUT;

	return 0;

}