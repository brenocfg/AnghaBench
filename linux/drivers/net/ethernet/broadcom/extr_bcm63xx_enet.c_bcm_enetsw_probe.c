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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  mtu; int /*<<< orphan*/  dev_addr; } ;
struct bcm_enet_priv {int enet_is_sw; int irq_rx; int irq_tx; int tx_chan; int /*<<< orphan*/  mac_clk; struct net_device* net_dev; struct platform_device* pdev; int /*<<< orphan*/  enetsw_mdio_lock; int /*<<< orphan*/  napi; int /*<<< orphan*/  rx_timeout; int /*<<< orphan*/  rx_lock; scalar_t__ rx_chan; int /*<<< orphan*/  base; int /*<<< orphan*/  dma_chan_width; int /*<<< orphan*/  dma_chan_int_mask; int /*<<< orphan*/  dma_chan_en_mask; int /*<<< orphan*/  dma_has_sram; int /*<<< orphan*/  num_ports; int /*<<< orphan*/  used_ports; int /*<<< orphan*/  dma_maxburst; int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  rx_ring_size; } ;
struct bcm63xx_enetsw_platform_data {int /*<<< orphan*/  dma_chan_width; int /*<<< orphan*/  dma_chan_int_mask; int /*<<< orphan*/  dma_chan_en_mask; int /*<<< orphan*/  dma_has_sram; int /*<<< orphan*/  num_ports; int /*<<< orphan*/  used_ports; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMENETSW_DMA_MAXBURST ; 
 int /*<<< orphan*/  BCMENET_DEF_RX_DESC ; 
 int /*<<< orphan*/  BCMENET_DEF_TX_DESC ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 int bcm_enet_change_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_enet_poll ; 
 int /*<<< orphan*/  bcm_enet_refill_rx_timer ; 
 int /*<<< orphan*/ * bcm_enet_shared_base ; 
 int /*<<< orphan*/  bcm_enetsw_ethtool_ops ; 
 int /*<<< orphan*/  bcm_enetsw_ops ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct bcm63xx_enetsw_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_enetsw_probe(struct platform_device *pdev)
{
	struct bcm_enet_priv *priv;
	struct net_device *dev;
	struct bcm63xx_enetsw_platform_data *pd;
	struct resource *res_mem;
	int ret, irq_rx, irq_tx;

	if (!bcm_enet_shared_base[0])
		return -EPROBE_DEFER;

	res_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	irq_rx = platform_get_irq(pdev, 0);
	irq_tx = platform_get_irq(pdev, 1);
	if (!res_mem || irq_rx < 0)
		return -ENODEV;

	ret = 0;
	dev = alloc_etherdev(sizeof(*priv));
	if (!dev)
		return -ENOMEM;
	priv = netdev_priv(dev);

	/* initialize default and fetch platform data */
	priv->enet_is_sw = true;
	priv->irq_rx = irq_rx;
	priv->irq_tx = irq_tx;
	priv->rx_ring_size = BCMENET_DEF_RX_DESC;
	priv->tx_ring_size = BCMENET_DEF_TX_DESC;
	priv->dma_maxburst = BCMENETSW_DMA_MAXBURST;

	pd = dev_get_platdata(&pdev->dev);
	if (pd) {
		memcpy(dev->dev_addr, pd->mac_addr, ETH_ALEN);
		memcpy(priv->used_ports, pd->used_ports,
		       sizeof(pd->used_ports));
		priv->num_ports = pd->num_ports;
		priv->dma_has_sram = pd->dma_has_sram;
		priv->dma_chan_en_mask = pd->dma_chan_en_mask;
		priv->dma_chan_int_mask = pd->dma_chan_int_mask;
		priv->dma_chan_width = pd->dma_chan_width;
	}

	ret = bcm_enet_change_mtu(dev, dev->mtu);
	if (ret)
		goto out;

	priv->base = devm_ioremap_resource(&pdev->dev, res_mem);
	if (IS_ERR(priv->base)) {
		ret = PTR_ERR(priv->base);
		goto out;
	}

	priv->mac_clk = devm_clk_get(&pdev->dev, "enetsw");
	if (IS_ERR(priv->mac_clk)) {
		ret = PTR_ERR(priv->mac_clk);
		goto out;
	}
	ret = clk_prepare_enable(priv->mac_clk);
	if (ret)
		goto out;

	priv->rx_chan = 0;
	priv->tx_chan = 1;
	spin_lock_init(&priv->rx_lock);

	/* init rx timeout (used for oom) */
	timer_setup(&priv->rx_timeout, bcm_enet_refill_rx_timer, 0);

	/* register netdevice */
	dev->netdev_ops = &bcm_enetsw_ops;
	netif_napi_add(dev, &priv->napi, bcm_enet_poll, 16);
	dev->ethtool_ops = &bcm_enetsw_ethtool_ops;
	SET_NETDEV_DEV(dev, &pdev->dev);

	spin_lock_init(&priv->enetsw_mdio_lock);

	ret = register_netdev(dev);
	if (ret)
		goto out_disable_clk;

	netif_carrier_off(dev);
	platform_set_drvdata(pdev, dev);
	priv->pdev = pdev;
	priv->net_dev = dev;

	return 0;

out_disable_clk:
	clk_disable_unprepare(priv->mac_clk);
out:
	free_netdev(dev);
	return ret;
}