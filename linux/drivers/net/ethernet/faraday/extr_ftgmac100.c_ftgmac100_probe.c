#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct phy_device {int dummy; } ;
struct net_device {int watchdog_timeo; int irq; int hw_features; int features; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * ethtool_ops; } ;
struct ftgmac100 {int tx_pause; int rx_pause; int aneg_pause; int is_aspeed; int use_ncsi; int /*<<< orphan*/  res; int /*<<< orphan*/  base; int /*<<< orphan*/  new_tx_q_entries; int /*<<< orphan*/  tx_q_entries; int /*<<< orphan*/  new_rx_q_entries; int /*<<< orphan*/  rx_q_entries; struct net_device* netdev; int /*<<< orphan*/  ndev; void* txdes0_edotr_mask; void* rxdes0_edorr_mask; int /*<<< orphan*/  reset_task; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 void* BIT (int) ; 
 int /*<<< orphan*/  CONFIG_NET_NCSI ; 
 int /*<<< orphan*/  DEF_RX_QUEUE_ENTRIES ; 
 int /*<<< orphan*/  DEF_TX_QUEUE_ENTRIES ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int NETIF_F_GRO ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_1__*) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ftgmac100_adjust_link ; 
 int /*<<< orphan*/  ftgmac100_destroy_mdio (struct net_device*) ; 
 int /*<<< orphan*/  ftgmac100_ethtool_ops ; 
 int /*<<< orphan*/  ftgmac100_initial_mac (struct ftgmac100*) ; 
 int /*<<< orphan*/  ftgmac100_ncsi_handler ; 
 int /*<<< orphan*/  ftgmac100_netdev_ops ; 
 int /*<<< orphan*/  ftgmac100_reset_task ; 
 int /*<<< orphan*/  ftgmac100_setup_clk (struct ftgmac100*) ; 
 int ftgmac100_setup_mdio (struct net_device*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncsi_register_dev (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int,int /*<<< orphan*/ ) ; 
 struct ftgmac100* netdev_priv (struct net_device*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_get_child_by_name (struct device_node*,char*) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct phy_device* of_phy_get_and_connect (struct net_device*,struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 int /*<<< orphan*/  phy_support_asym_pause (struct phy_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int ftgmac100_probe(struct platform_device *pdev)
{
	struct resource *res;
	int irq;
	struct net_device *netdev;
	struct ftgmac100 *priv;
	struct device_node *np;
	int err = 0;

	if (!pdev)
		return -ENODEV;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENXIO;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	/* setup net_device */
	netdev = alloc_etherdev(sizeof(*priv));
	if (!netdev) {
		err = -ENOMEM;
		goto err_alloc_etherdev;
	}

	SET_NETDEV_DEV(netdev, &pdev->dev);

	netdev->ethtool_ops = &ftgmac100_ethtool_ops;
	netdev->netdev_ops = &ftgmac100_netdev_ops;
	netdev->watchdog_timeo = 5 * HZ;

	platform_set_drvdata(pdev, netdev);

	/* setup private data */
	priv = netdev_priv(netdev);
	priv->netdev = netdev;
	priv->dev = &pdev->dev;
	INIT_WORK(&priv->reset_task, ftgmac100_reset_task);

	/* map io memory */
	priv->res = request_mem_region(res->start, resource_size(res),
				       dev_name(&pdev->dev));
	if (!priv->res) {
		dev_err(&pdev->dev, "Could not reserve memory region\n");
		err = -ENOMEM;
		goto err_req_mem;
	}

	priv->base = ioremap(res->start, resource_size(res));
	if (!priv->base) {
		dev_err(&pdev->dev, "Failed to ioremap ethernet registers\n");
		err = -EIO;
		goto err_ioremap;
	}

	netdev->irq = irq;

	/* Enable pause */
	priv->tx_pause = true;
	priv->rx_pause = true;
	priv->aneg_pause = true;

	/* MAC address from chip or random one */
	ftgmac100_initial_mac(priv);

	np = pdev->dev.of_node;
	if (np && (of_device_is_compatible(np, "aspeed,ast2400-mac") ||
		   of_device_is_compatible(np, "aspeed,ast2500-mac") ||
		   of_device_is_compatible(np, "aspeed,ast2600-mac"))) {
		priv->rxdes0_edorr_mask = BIT(30);
		priv->txdes0_edotr_mask = BIT(30);
		priv->is_aspeed = true;
	} else {
		priv->rxdes0_edorr_mask = BIT(15);
		priv->txdes0_edotr_mask = BIT(15);
	}

	if (np && of_get_property(np, "use-ncsi", NULL)) {
		if (!IS_ENABLED(CONFIG_NET_NCSI)) {
			dev_err(&pdev->dev, "NCSI stack not enabled\n");
			goto err_ncsi_dev;
		}

		dev_info(&pdev->dev, "Using NCSI interface\n");
		priv->use_ncsi = true;
		priv->ndev = ncsi_register_dev(netdev, ftgmac100_ncsi_handler);
		if (!priv->ndev)
			goto err_ncsi_dev;
	} else if (np && of_get_property(np, "phy-handle", NULL)) {
		struct phy_device *phy;

		phy = of_phy_get_and_connect(priv->netdev, np,
					     &ftgmac100_adjust_link);
		if (!phy) {
			dev_err(&pdev->dev, "Failed to connect to phy\n");
			goto err_setup_mdio;
		}

		/* Indicate that we support PAUSE frames (see comment in
		 * Documentation/networking/phy.txt)
		 */
		phy_support_asym_pause(phy);

		/* Display what we found */
		phy_attached_info(phy);
	} else if (np && !of_get_child_by_name(np, "mdio")) {
		/* Support legacy ASPEED devicetree descriptions that decribe a
		 * MAC with an embedded MDIO controller but have no "mdio"
		 * child node. Automatically scan the MDIO bus for available
		 * PHYs.
		 */
		priv->use_ncsi = false;
		err = ftgmac100_setup_mdio(netdev);
		if (err)
			goto err_setup_mdio;
	}

	if (priv->is_aspeed)
		ftgmac100_setup_clk(priv);

	/* Default ring sizes */
	priv->rx_q_entries = priv->new_rx_q_entries = DEF_RX_QUEUE_ENTRIES;
	priv->tx_q_entries = priv->new_tx_q_entries = DEF_TX_QUEUE_ENTRIES;

	/* Base feature set */
	netdev->hw_features = NETIF_F_RXCSUM | NETIF_F_HW_CSUM |
		NETIF_F_GRO | NETIF_F_SG | NETIF_F_HW_VLAN_CTAG_RX |
		NETIF_F_HW_VLAN_CTAG_TX;

	if (priv->use_ncsi)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	/* AST2400  doesn't have working HW checksum generation */
	if (np && (of_device_is_compatible(np, "aspeed,ast2400-mac")))
		netdev->hw_features &= ~NETIF_F_HW_CSUM;
	if (np && of_get_property(np, "no-hw-checksum", NULL))
		netdev->hw_features &= ~(NETIF_F_HW_CSUM | NETIF_F_RXCSUM);
	netdev->features |= netdev->hw_features;

	/* register network device */
	err = register_netdev(netdev);
	if (err) {
		dev_err(&pdev->dev, "Failed to register netdev\n");
		goto err_register_netdev;
	}

	netdev_info(netdev, "irq %d, mapped at %p\n", netdev->irq, priv->base);

	return 0;

err_ncsi_dev:
err_register_netdev:
	ftgmac100_destroy_mdio(netdev);
err_setup_mdio:
	iounmap(priv->base);
err_ioremap:
	release_resource(priv->res);
err_req_mem:
	free_netdev(netdev);
err_alloc_etherdev:
	return err;
}