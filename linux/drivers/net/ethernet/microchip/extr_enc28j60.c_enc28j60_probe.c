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
struct spi_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  irq; int /*<<< orphan*/  if_port; int /*<<< orphan*/  dev_addr; } ;
struct enc28j60_net {int /*<<< orphan*/  restart_work; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  setrx_work; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  lock; int /*<<< orphan*/  msg_enable; struct spi_device* spi; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  macaddr ;
struct TYPE_3__ {int /*<<< orphan*/  msg_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  DRV_VERSION ; 
 int EIO ; 
 int /*<<< orphan*/  ENC28J60_MSG_DEFAULT ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  IF_PORT_10BASET ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 struct net_device* alloc_etherdev (int) ; 
 TYPE_1__ debug ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ device_get_mac_address (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  enc28j60_chipset_init (struct net_device*) ; 
 int /*<<< orphan*/  enc28j60_ethtool_ops ; 
 int /*<<< orphan*/  enc28j60_irq ; 
 int /*<<< orphan*/  enc28j60_irq_work_handler ; 
 int /*<<< orphan*/  enc28j60_lowpower (struct enc28j60_net*,int) ; 
 int /*<<< orphan*/  enc28j60_netdev_ops ; 
 int /*<<< orphan*/  enc28j60_restart_work_handler ; 
 int /*<<< orphan*/  enc28j60_set_hw_macaddr (struct net_device*) ; 
 int /*<<< orphan*/  enc28j60_setrx_work_handler ; 
 int /*<<< orphan*/  enc28j60_tx_work_handler ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct enc28j60_net*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct enc28j60_net* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_drv (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_msg_probe (struct enc28j60_net*) ; 
 int register_netdev (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct enc28j60_net*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct enc28j60_net*) ; 

__attribute__((used)) static int enc28j60_probe(struct spi_device *spi)
{
	unsigned char macaddr[ETH_ALEN];
	struct net_device *dev;
	struct enc28j60_net *priv;
	int ret = 0;

	if (netif_msg_drv(&debug))
		dev_info(&spi->dev, "Ethernet driver %s loaded\n", DRV_VERSION);

	dev = alloc_etherdev(sizeof(struct enc28j60_net));
	if (!dev) {
		ret = -ENOMEM;
		goto error_alloc;
	}
	priv = netdev_priv(dev);

	priv->netdev = dev;	/* priv to netdev reference */
	priv->spi = spi;	/* priv to spi reference */
	priv->msg_enable = netif_msg_init(debug.msg_enable, ENC28J60_MSG_DEFAULT);
	mutex_init(&priv->lock);
	INIT_WORK(&priv->tx_work, enc28j60_tx_work_handler);
	INIT_WORK(&priv->setrx_work, enc28j60_setrx_work_handler);
	INIT_WORK(&priv->irq_work, enc28j60_irq_work_handler);
	INIT_WORK(&priv->restart_work, enc28j60_restart_work_handler);
	spi_set_drvdata(spi, priv);	/* spi to priv reference */
	SET_NETDEV_DEV(dev, &spi->dev);

	if (!enc28j60_chipset_init(dev)) {
		if (netif_msg_probe(priv))
			dev_info(&spi->dev, "chip not found\n");
		ret = -EIO;
		goto error_irq;
	}

	if (device_get_mac_address(&spi->dev, macaddr, sizeof(macaddr)))
		ether_addr_copy(dev->dev_addr, macaddr);
	else
		eth_hw_addr_random(dev);
	enc28j60_set_hw_macaddr(dev);

	/* Board setup must set the relevant edge trigger type;
	 * level triggers won't currently work.
	 */
	ret = request_irq(spi->irq, enc28j60_irq, 0, DRV_NAME, priv);
	if (ret < 0) {
		if (netif_msg_probe(priv))
			dev_err(&spi->dev, "request irq %d failed (ret = %d)\n",
				spi->irq, ret);
		goto error_irq;
	}

	dev->if_port = IF_PORT_10BASET;
	dev->irq = spi->irq;
	dev->netdev_ops = &enc28j60_netdev_ops;
	dev->watchdog_timeo = TX_TIMEOUT;
	dev->ethtool_ops = &enc28j60_ethtool_ops;

	enc28j60_lowpower(priv, true);

	ret = register_netdev(dev);
	if (ret) {
		if (netif_msg_probe(priv))
			dev_err(&spi->dev, "register netdev failed (ret = %d)\n",
				ret);
		goto error_register;
	}

	return 0;

error_register:
	free_irq(spi->irq, priv);
error_irq:
	free_netdev(dev);
error_alloc:
	return ret;
}