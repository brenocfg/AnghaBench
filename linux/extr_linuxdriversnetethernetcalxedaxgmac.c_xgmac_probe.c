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
typedef  int u32 ;
struct xgmac_priv {int rx_pause; int tx_pause; int max_macs; int pmt_irq; scalar_t__ base; int /*<<< orphan*/  napi; int /*<<< orphan*/  wolopts; int /*<<< orphan*/ * device; struct net_device* dev; int /*<<< orphan*/  tx_timeout_work; int /*<<< orphan*/  stats_lock; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct net_device {int irq; int hw_features; int features; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  max_mtu; scalar_t__ min_mtu; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int DMA_HW_FEAT_TXCOESEL ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ ETH_HLEN ; 
 scalar_t__ ETH_ZLEN ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WAKE_MAGIC ; 
 scalar_t__ XGMAC_ADDR_HIGH (int) ; 
 scalar_t__ XGMAC_DMA_HW_FEATURE ; 
 scalar_t__ XGMAC_DMA_INTR_ENA ; 
 int /*<<< orphan*/  XGMAC_MAX_MTU ; 
 scalar_t__ XGMAC_VERSION ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ device_can_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_irq (int,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 struct xgmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int readl (scalar_t__) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  xgmac_ethtool_ops ; 
 int /*<<< orphan*/  xgmac_get_mac_addr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgmac_interrupt ; 
 int /*<<< orphan*/  xgmac_netdev_ops ; 
 int /*<<< orphan*/  xgmac_pmt_interrupt ; 
 int /*<<< orphan*/  xgmac_poll ; 
 int /*<<< orphan*/  xgmac_tx_timeout_work ; 

__attribute__((used)) static int xgmac_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct resource *res;
	struct net_device *ndev = NULL;
	struct xgmac_priv *priv = NULL;
	u32 uid;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	if (!request_mem_region(res->start, resource_size(res), pdev->name))
		return -EBUSY;

	ndev = alloc_etherdev(sizeof(struct xgmac_priv));
	if (!ndev) {
		ret = -ENOMEM;
		goto err_alloc;
	}

	SET_NETDEV_DEV(ndev, &pdev->dev);
	priv = netdev_priv(ndev);
	platform_set_drvdata(pdev, ndev);
	ndev->netdev_ops = &xgmac_netdev_ops;
	ndev->ethtool_ops = &xgmac_ethtool_ops;
	spin_lock_init(&priv->stats_lock);
	INIT_WORK(&priv->tx_timeout_work, xgmac_tx_timeout_work);

	priv->device = &pdev->dev;
	priv->dev = ndev;
	priv->rx_pause = 1;
	priv->tx_pause = 1;

	priv->base = ioremap(res->start, resource_size(res));
	if (!priv->base) {
		netdev_err(ndev, "ioremap failed\n");
		ret = -ENOMEM;
		goto err_io;
	}

	uid = readl(priv->base + XGMAC_VERSION);
	netdev_info(ndev, "h/w version is 0x%x\n", uid);

	/* Figure out how many valid mac address filter registers we have */
	writel(1, priv->base + XGMAC_ADDR_HIGH(31));
	if (readl(priv->base + XGMAC_ADDR_HIGH(31)) == 1)
		priv->max_macs = 31;
	else
		priv->max_macs = 7;

	writel(0, priv->base + XGMAC_DMA_INTR_ENA);
	ndev->irq = platform_get_irq(pdev, 0);
	if (ndev->irq == -ENXIO) {
		netdev_err(ndev, "No irq resource\n");
		ret = ndev->irq;
		goto err_irq;
	}

	ret = request_irq(ndev->irq, xgmac_interrupt, 0,
			  dev_name(&pdev->dev), ndev);
	if (ret < 0) {
		netdev_err(ndev, "Could not request irq %d - ret %d)\n",
			ndev->irq, ret);
		goto err_irq;
	}

	priv->pmt_irq = platform_get_irq(pdev, 1);
	if (priv->pmt_irq == -ENXIO) {
		netdev_err(ndev, "No pmt irq resource\n");
		ret = priv->pmt_irq;
		goto err_pmt_irq;
	}

	ret = request_irq(priv->pmt_irq, xgmac_pmt_interrupt, 0,
			  dev_name(&pdev->dev), ndev);
	if (ret < 0) {
		netdev_err(ndev, "Could not request irq %d - ret %d)\n",
			priv->pmt_irq, ret);
		goto err_pmt_irq;
	}

	device_set_wakeup_capable(&pdev->dev, 1);
	if (device_can_wakeup(priv->device))
		priv->wolopts = WAKE_MAGIC;	/* Magic Frame as default */

	ndev->hw_features = NETIF_F_SG | NETIF_F_HIGHDMA;
	if (readl(priv->base + XGMAC_DMA_HW_FEATURE) & DMA_HW_FEAT_TXCOESEL)
		ndev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				     NETIF_F_RXCSUM;
	ndev->features |= ndev->hw_features;
	ndev->priv_flags |= IFF_UNICAST_FLT;

	/* MTU range: 46 - 9000 */
	ndev->min_mtu = ETH_ZLEN - ETH_HLEN;
	ndev->max_mtu = XGMAC_MAX_MTU;

	/* Get the MAC address */
	xgmac_get_mac_addr(priv->base, ndev->dev_addr, 0);
	if (!is_valid_ether_addr(ndev->dev_addr))
		netdev_warn(ndev, "MAC address %pM not valid",
			 ndev->dev_addr);

	netif_napi_add(ndev, &priv->napi, xgmac_poll, 64);
	ret = register_netdev(ndev);
	if (ret)
		goto err_reg;

	return 0;

err_reg:
	netif_napi_del(&priv->napi);
	free_irq(priv->pmt_irq, ndev);
err_pmt_irq:
	free_irq(ndev->irq, ndev);
err_irq:
	iounmap(priv->base);
err_io:
	free_netdev(ndev);
err_alloc:
	release_mem_region(res->start, resource_size(res));
	return ret;
}