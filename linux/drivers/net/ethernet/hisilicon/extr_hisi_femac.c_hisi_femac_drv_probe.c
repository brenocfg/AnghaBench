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
struct device {struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct phy_device {int /*<<< orphan*/  interface; scalar_t__ phy_id; } ;
struct net_device {int watchdog_timeo; int /*<<< orphan*/  irq; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  dev_addr; } ;
struct hisi_femac_priv {char const* port_base; char const* glb_base; char const* clk; char const* mac_rst; char const* phy_rst; int /*<<< orphan*/  napi; int /*<<< orphan*/  phy_reset_delays; struct net_device* ndev; struct device* dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAYS_NUM ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FEMAC_POLL_WEIGHT ; 
 int HZ ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (char const*) ; 
 int /*<<< orphan*/  PHY_RESET_DELAYS_PROPERTY ; 
 int PTR_ERR (char const*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (char const*) ; 
 int clk_prepare_enable (char const*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ) ; 
 char const* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 void* devm_reset_control_get (struct device*,char*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hisi_femac_adjust_link ; 
 int /*<<< orphan*/  hisi_femac_core_reset (struct hisi_femac_priv*) ; 
 int /*<<< orphan*/  hisi_femac_ethtools_ops ; 
 int hisi_femac_init_tx_and_rx_queues (struct hisi_femac_priv*) ; 
 int /*<<< orphan*/  hisi_femac_interrupt ; 
 int /*<<< orphan*/  hisi_femac_netdev_ops ; 
 int /*<<< orphan*/  hisi_femac_phy_reset (struct hisi_femac_priv*) ; 
 int /*<<< orphan*/  hisi_femac_poll ; 
 int /*<<< orphan*/  hisi_femac_port_init (struct hisi_femac_priv*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct hisi_femac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 char* of_get_mac_address (struct device_node*) ; 
 struct phy_device* of_phy_get_and_connect (struct net_device*,struct device_node*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32_array (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_attached_print (struct phy_device*,char*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int /*<<< orphan*/  phy_modes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static int hisi_femac_drv_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct net_device *ndev;
	struct hisi_femac_priv *priv;
	struct phy_device *phy;
	const char *mac_addr;
	int ret;

	ndev = alloc_etherdev(sizeof(*priv));
	if (!ndev)
		return -ENOMEM;

	platform_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);

	priv = netdev_priv(ndev);
	priv->dev = dev;
	priv->ndev = ndev;

	priv->port_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->port_base)) {
		ret = PTR_ERR(priv->port_base);
		goto out_free_netdev;
	}

	priv->glb_base = devm_platform_ioremap_resource(pdev, 1);
	if (IS_ERR(priv->glb_base)) {
		ret = PTR_ERR(priv->glb_base);
		goto out_free_netdev;
	}

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(priv->clk)) {
		dev_err(dev, "failed to get clk\n");
		ret = -ENODEV;
		goto out_free_netdev;
	}

	ret = clk_prepare_enable(priv->clk);
	if (ret) {
		dev_err(dev, "failed to enable clk %d\n", ret);
		goto out_free_netdev;
	}

	priv->mac_rst = devm_reset_control_get(dev, "mac");
	if (IS_ERR(priv->mac_rst)) {
		ret = PTR_ERR(priv->mac_rst);
		goto out_disable_clk;
	}
	hisi_femac_core_reset(priv);

	priv->phy_rst = devm_reset_control_get(dev, "phy");
	if (IS_ERR(priv->phy_rst)) {
		priv->phy_rst = NULL;
	} else {
		ret = of_property_read_u32_array(node,
						 PHY_RESET_DELAYS_PROPERTY,
						 priv->phy_reset_delays,
						 DELAYS_NUM);
		if (ret)
			goto out_disable_clk;
		hisi_femac_phy_reset(priv);
	}

	phy = of_phy_get_and_connect(ndev, node, hisi_femac_adjust_link);
	if (!phy) {
		dev_err(dev, "connect to PHY failed!\n");
		ret = -ENODEV;
		goto out_disable_clk;
	}

	phy_attached_print(phy, "phy_id=0x%.8lx, phy_mode=%s\n",
			   (unsigned long)phy->phy_id,
			   phy_modes(phy->interface));

	mac_addr = of_get_mac_address(node);
	if (!IS_ERR(mac_addr))
		ether_addr_copy(ndev->dev_addr, mac_addr);
	if (!is_valid_ether_addr(ndev->dev_addr)) {
		eth_hw_addr_random(ndev);
		dev_warn(dev, "using random MAC address %pM\n",
			 ndev->dev_addr);
	}

	ndev->watchdog_timeo = 6 * HZ;
	ndev->priv_flags |= IFF_UNICAST_FLT;
	ndev->netdev_ops = &hisi_femac_netdev_ops;
	ndev->ethtool_ops = &hisi_femac_ethtools_ops;
	netif_napi_add(ndev, &priv->napi, hisi_femac_poll, FEMAC_POLL_WEIGHT);

	hisi_femac_port_init(priv);

	ret = hisi_femac_init_tx_and_rx_queues(priv);
	if (ret)
		goto out_disconnect_phy;

	ndev->irq = platform_get_irq(pdev, 0);
	if (ndev->irq <= 0) {
		ret = -ENODEV;
		goto out_disconnect_phy;
	}

	ret = devm_request_irq(dev, ndev->irq, hisi_femac_interrupt,
			       IRQF_SHARED, pdev->name, ndev);
	if (ret) {
		dev_err(dev, "devm_request_irq %d failed!\n", ndev->irq);
		goto out_disconnect_phy;
	}

	ret = register_netdev(ndev);
	if (ret) {
		dev_err(dev, "register_netdev failed!\n");
		goto out_disconnect_phy;
	}

	return ret;

out_disconnect_phy:
	netif_napi_del(&priv->napi);
	phy_disconnect(phy);
out_disable_clk:
	clk_disable_unprepare(priv->clk);
out_free_netdev:
	free_netdev(ndev);

	return ret;
}