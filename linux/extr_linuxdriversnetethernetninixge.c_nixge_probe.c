#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct resource {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct nixge_priv {scalar_t__ tx_irq; scalar_t__ rx_irq; scalar_t__ phy_mode; int /*<<< orphan*/  mii_bus; struct net_device* ndev; int /*<<< orphan*/  phy_node; int /*<<< orphan*/  coalesce_count_tx; int /*<<< orphan*/  coalesce_count_rx; scalar_t__ dma_regs; scalar_t__ ctrl_regs; int /*<<< orphan*/  napi; TYPE_1__* dev; } ;
struct net_device {int min_mtu; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  NETIF_F_SG ; 
 int /*<<< orphan*/  NIXGE_JUMBO_MTU ; 
 scalar_t__ NIXGE_REG_CTRL_OFFSET ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  XAXIDMA_DFT_RX_THRESHOLD ; 
 int /*<<< orphan*/  XAXIDMA_DFT_TX_THRESHOLD ; 
 int /*<<< orphan*/  __nixge_hw_set_mac_address (struct net_device*) ; 
 struct net_device* alloc_etherdev (int) ; 
 scalar_t__ devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct nixge_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nixge_ethtool_ops ; 
 int /*<<< orphan*/ * nixge_get_nvmem_address (TYPE_1__*) ; 
 int nixge_mdio_setup (struct nixge_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nixge_netdev_ops ; 
 int /*<<< orphan*/  nixge_poll ; 
 scalar_t__ of_get_phy_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static int nixge_probe(struct platform_device *pdev)
{
	struct nixge_priv *priv;
	struct net_device *ndev;
	struct resource *dmares;
	const u8 *mac_addr;
	int err;

	ndev = alloc_etherdev(sizeof(*priv));
	if (!ndev)
		return -ENOMEM;

	platform_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);

	ndev->features = NETIF_F_SG;
	ndev->netdev_ops = &nixge_netdev_ops;
	ndev->ethtool_ops = &nixge_ethtool_ops;

	/* MTU range: 64 - 9000 */
	ndev->min_mtu = 64;
	ndev->max_mtu = NIXGE_JUMBO_MTU;

	mac_addr = nixge_get_nvmem_address(&pdev->dev);
	if (mac_addr && is_valid_ether_addr(mac_addr)) {
		ether_addr_copy(ndev->dev_addr, mac_addr);
		kfree(mac_addr);
	} else {
		eth_hw_addr_random(ndev);
	}

	priv = netdev_priv(ndev);
	priv->ndev = ndev;
	priv->dev = &pdev->dev;

	netif_napi_add(ndev, &priv->napi, nixge_poll, NAPI_POLL_WEIGHT);

	dmares = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->dma_regs = devm_ioremap_resource(&pdev->dev, dmares);
	if (IS_ERR(priv->dma_regs)) {
		netdev_err(ndev, "failed to map dma regs\n");
		return PTR_ERR(priv->dma_regs);
	}
	priv->ctrl_regs = priv->dma_regs + NIXGE_REG_CTRL_OFFSET;
	__nixge_hw_set_mac_address(ndev);

	priv->tx_irq = platform_get_irq_byname(pdev, "tx");
	if (priv->tx_irq < 0) {
		netdev_err(ndev, "could not find 'tx' irq");
		return priv->tx_irq;
	}

	priv->rx_irq = platform_get_irq_byname(pdev, "rx");
	if (priv->rx_irq < 0) {
		netdev_err(ndev, "could not find 'rx' irq");
		return priv->rx_irq;
	}

	priv->coalesce_count_rx = XAXIDMA_DFT_RX_THRESHOLD;
	priv->coalesce_count_tx = XAXIDMA_DFT_TX_THRESHOLD;

	err = nixge_mdio_setup(priv, pdev->dev.of_node);
	if (err) {
		netdev_err(ndev, "error registering mdio bus");
		goto free_netdev;
	}

	priv->phy_mode = of_get_phy_mode(pdev->dev.of_node);
	if (priv->phy_mode < 0) {
		netdev_err(ndev, "not find \"phy-mode\" property\n");
		err = -EINVAL;
		goto unregister_mdio;
	}

	priv->phy_node = of_parse_phandle(pdev->dev.of_node, "phy-handle", 0);
	if (!priv->phy_node) {
		netdev_err(ndev, "not find \"phy-handle\" property\n");
		err = -EINVAL;
		goto unregister_mdio;
	}

	err = register_netdev(priv->ndev);
	if (err) {
		netdev_err(ndev, "register_netdev() error (%i)\n", err);
		goto unregister_mdio;
	}

	return 0;

unregister_mdio:
	mdiobus_unregister(priv->mii_bus);

free_netdev:
	free_netdev(ndev);

	return err;
}