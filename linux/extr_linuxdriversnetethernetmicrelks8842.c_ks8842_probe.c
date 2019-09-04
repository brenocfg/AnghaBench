#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct resource {int flags; int /*<<< orphan*/  start; } ;
struct TYPE_7__ {struct TYPE_7__* parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct net_device {unsigned int addr_len; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct ks8842_platform_data {int tx_dma_channel; int rx_dma_channel; scalar_t__* macaddr; } ;
struct TYPE_6__ {int channel; } ;
struct TYPE_5__ {int channel; } ;
struct ks8842_adapter {int conf_flags; int irq; int /*<<< orphan*/  hw_addr; int /*<<< orphan*/  lock; int /*<<< orphan*/  tasklet; TYPE_2__ dma_tx; TYPE_1__ dma_rx; TYPE_3__* dev; int /*<<< orphan*/  timeout_work; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int MICREL_KS884X ; 
 int /*<<< orphan*/  REG_SW_ID_AND_ENABLE ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_3__*) ; 
 struct net_device* alloc_etherdev (int) ; 
 struct ks8842_platform_data* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks8842_ethtool_ops ; 
 int /*<<< orphan*/  ks8842_netdev_ops ; 
 int ks8842_read16 (struct ks8842_adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks8842_read_mac_addr (struct ks8842_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks8842_tasklet ; 
 int /*<<< orphan*/  ks8842_tx_timeout_work ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,unsigned int) ; 
 struct ks8842_adapter* netdev_priv (struct net_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,int) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ks8842_probe(struct platform_device *pdev)
{
	int err = -ENOMEM;
	struct resource *iomem;
	struct net_device *netdev;
	struct ks8842_adapter *adapter;
	struct ks8842_platform_data *pdata = dev_get_platdata(&pdev->dev);
	u16 id;
	unsigned i;

	iomem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!request_mem_region(iomem->start, resource_size(iomem), DRV_NAME))
		goto err_mem_region;

	netdev = alloc_etherdev(sizeof(struct ks8842_adapter));
	if (!netdev)
		goto err_alloc_etherdev;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	INIT_WORK(&adapter->timeout_work, ks8842_tx_timeout_work);
	adapter->hw_addr = ioremap(iomem->start, resource_size(iomem));
	adapter->conf_flags = iomem->flags;

	if (!adapter->hw_addr)
		goto err_ioremap;

	adapter->irq = platform_get_irq(pdev, 0);
	if (adapter->irq < 0) {
		err = adapter->irq;
		goto err_get_irq;
	}

	adapter->dev = (pdev->dev.parent) ? pdev->dev.parent : &pdev->dev;

	/* DMA is only supported when accessed via timberdale */
	if (!(adapter->conf_flags & MICREL_KS884X) && pdata &&
		(pdata->tx_dma_channel != -1) &&
		(pdata->rx_dma_channel != -1)) {
		adapter->dma_rx.channel = pdata->rx_dma_channel;
		adapter->dma_tx.channel = pdata->tx_dma_channel;
	} else {
		adapter->dma_rx.channel = -1;
		adapter->dma_tx.channel = -1;
	}

	tasklet_init(&adapter->tasklet, ks8842_tasklet, (unsigned long)netdev);
	spin_lock_init(&adapter->lock);

	netdev->netdev_ops = &ks8842_netdev_ops;
	netdev->ethtool_ops = &ks8842_ethtool_ops;

	/* Check if a mac address was given */
	i = netdev->addr_len;
	if (pdata) {
		for (i = 0; i < netdev->addr_len; i++)
			if (pdata->macaddr[i] != 0)
				break;

		if (i < netdev->addr_len)
			/* an address was passed, use it */
			memcpy(netdev->dev_addr, pdata->macaddr,
				netdev->addr_len);
	}

	if (i == netdev->addr_len) {
		ks8842_read_mac_addr(adapter, netdev->dev_addr);

		if (!is_valid_ether_addr(netdev->dev_addr))
			eth_hw_addr_random(netdev);
	}

	id = ks8842_read16(adapter, 32, REG_SW_ID_AND_ENABLE);

	strcpy(netdev->name, "eth%d");
	err = register_netdev(netdev);
	if (err)
		goto err_register;

	platform_set_drvdata(pdev, netdev);

	pr_info("Found chip, family: 0x%x, id: 0x%x, rev: 0x%x\n",
		(id >> 8) & 0xff, (id >> 4) & 0xf, (id >> 1) & 0x7);

	return 0;

err_register:
err_get_irq:
	iounmap(adapter->hw_addr);
err_ioremap:
	free_netdev(netdev);
err_alloc_etherdev:
	release_mem_region(iomem->start, resource_size(iomem));
err_mem_region:
	return err;
}