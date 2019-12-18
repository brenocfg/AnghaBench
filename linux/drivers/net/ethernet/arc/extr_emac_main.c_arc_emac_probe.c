#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct phy_device {int /*<<< orphan*/  phy_id; TYPE_2__* drv; } ;
struct TYPE_3__ {struct device* parent; } ;
struct net_device {unsigned int irq; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct arc_emac_priv {char const* regs; scalar_t__ clk; int /*<<< orphan*/  napi; scalar_t__ txbd_dma; scalar_t__ rxbd_dma; scalar_t__ rxbd; scalar_t__ txbd; struct device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_EMAC_NAPI_WEIGHT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (char const*) ; 
 int PTR_ERR (char const*) ; 
 scalar_t__ RX_BD_NUM ; 
 scalar_t__ RX_RING_SZ ; 
 int /*<<< orphan*/  R_ID ; 
 int /*<<< orphan*/  R_POLLRATE ; 
 scalar_t__ TX_RING_SZ ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 int /*<<< orphan*/  arc_emac_adjust_link ; 
 int /*<<< orphan*/  arc_emac_ethtool_ops ; 
 int /*<<< orphan*/  arc_emac_intr ; 
 int /*<<< orphan*/  arc_emac_netdev_ops ; 
 int /*<<< orphan*/  arc_emac_poll ; 
 int /*<<< orphan*/  arc_emac_set_address_internal (struct net_device*) ; 
 int arc_mdio_probe (struct arc_emac_priv*) ; 
 int /*<<< orphan*/  arc_mdio_remove (struct arc_emac_priv*) ; 
 unsigned int arc_reg_get (struct arc_emac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_reg_set (struct arc_emac_priv*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 unsigned int clk_get_rate (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,unsigned int,...) ; 
 char const* devm_ioremap_resource (struct device*,struct resource*) ; 
 int devm_request_irq (struct device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 scalar_t__ dmam_alloc_coherent (struct device*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,char const*) ; 
 unsigned int irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct arc_emac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int of_address_to_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 char* of_get_mac_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct phy_device* of_phy_connect (struct net_device*,struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int register_netdev (struct net_device*) ; 

int arc_emac_probe(struct net_device *ndev, int interface)
{
	struct device *dev = ndev->dev.parent;
	struct resource res_regs;
	struct device_node *phy_node;
	struct phy_device *phydev = NULL;
	struct arc_emac_priv *priv;
	const char *mac_addr;
	unsigned int id, clock_frequency, irq;
	int err;

	/* Get PHY from device tree */
	phy_node = of_parse_phandle(dev->of_node, "phy", 0);
	if (!phy_node) {
		dev_err(dev, "failed to retrieve phy description from device tree\n");
		return -ENODEV;
	}

	/* Get EMAC registers base address from device tree */
	err = of_address_to_resource(dev->of_node, 0, &res_regs);
	if (err) {
		dev_err(dev, "failed to retrieve registers base from device tree\n");
		err = -ENODEV;
		goto out_put_node;
	}

	/* Get IRQ from device tree */
	irq = irq_of_parse_and_map(dev->of_node, 0);
	if (!irq) {
		dev_err(dev, "failed to retrieve <irq> value from device tree\n");
		err = -ENODEV;
		goto out_put_node;
	}

	ndev->netdev_ops = &arc_emac_netdev_ops;
	ndev->ethtool_ops = &arc_emac_ethtool_ops;
	ndev->watchdog_timeo = TX_TIMEOUT;

	priv = netdev_priv(ndev);
	priv->dev = dev;

	priv->regs = devm_ioremap_resource(dev, &res_regs);
	if (IS_ERR(priv->regs)) {
		err = PTR_ERR(priv->regs);
		goto out_put_node;
	}

	dev_dbg(dev, "Registers base address is 0x%p\n", priv->regs);

	if (priv->clk) {
		err = clk_prepare_enable(priv->clk);
		if (err) {
			dev_err(dev, "failed to enable clock\n");
			goto out_put_node;
		}

		clock_frequency = clk_get_rate(priv->clk);
	} else {
		/* Get CPU clock frequency from device tree */
		if (of_property_read_u32(dev->of_node, "clock-frequency",
					 &clock_frequency)) {
			dev_err(dev, "failed to retrieve <clock-frequency> from device tree\n");
			err = -EINVAL;
			goto out_put_node;
		}
	}

	id = arc_reg_get(priv, R_ID);

	/* Check for EMAC revision 5 or 7, magic number */
	if (!(id == 0x0005fd02 || id == 0x0007fd02)) {
		dev_err(dev, "ARC EMAC not detected, id=0x%x\n", id);
		err = -ENODEV;
		goto out_clken;
	}
	dev_info(dev, "ARC EMAC detected with id: 0x%x\n", id);

	/* Set poll rate so that it polls every 1 ms */
	arc_reg_set(priv, R_POLLRATE, clock_frequency / 1000000);

	ndev->irq = irq;
	dev_info(dev, "IRQ is %d\n", ndev->irq);

	/* Register interrupt handler for device */
	err = devm_request_irq(dev, ndev->irq, arc_emac_intr, 0,
			       ndev->name, ndev);
	if (err) {
		dev_err(dev, "could not allocate IRQ\n");
		goto out_clken;
	}

	/* Get MAC address from device tree */
	mac_addr = of_get_mac_address(dev->of_node);

	if (!IS_ERR(mac_addr))
		ether_addr_copy(ndev->dev_addr, mac_addr);
	else
		eth_hw_addr_random(ndev);

	arc_emac_set_address_internal(ndev);
	dev_info(dev, "MAC address is now %pM\n", ndev->dev_addr);

	/* Do 1 allocation instead of 2 separate ones for Rx and Tx BD rings */
	priv->rxbd = dmam_alloc_coherent(dev, RX_RING_SZ + TX_RING_SZ,
					 &priv->rxbd_dma, GFP_KERNEL);

	if (!priv->rxbd) {
		dev_err(dev, "failed to allocate data buffers\n");
		err = -ENOMEM;
		goto out_clken;
	}

	priv->txbd = priv->rxbd + RX_BD_NUM;

	priv->txbd_dma = priv->rxbd_dma + RX_RING_SZ;
	dev_dbg(dev, "EMAC Device addr: Rx Ring [0x%x], Tx Ring[%x]\n",
		(unsigned int)priv->rxbd_dma, (unsigned int)priv->txbd_dma);

	err = arc_mdio_probe(priv);
	if (err) {
		dev_err(dev, "failed to probe MII bus\n");
		goto out_clken;
	}

	phydev = of_phy_connect(ndev, phy_node, arc_emac_adjust_link, 0,
				interface);
	if (!phydev) {
		dev_err(dev, "of_phy_connect() failed\n");
		err = -ENODEV;
		goto out_mdio;
	}

	dev_info(dev, "connected to %s phy with id 0x%x\n",
		 phydev->drv->name, phydev->phy_id);

	netif_napi_add(ndev, &priv->napi, arc_emac_poll, ARC_EMAC_NAPI_WEIGHT);

	err = register_netdev(ndev);
	if (err) {
		dev_err(dev, "failed to register network device\n");
		goto out_netif_api;
	}

	of_node_put(phy_node);
	return 0;

out_netif_api:
	netif_napi_del(&priv->napi);
	phy_disconnect(phydev);
out_mdio:
	arc_mdio_remove(priv);
out_clken:
	if (priv->clk)
		clk_disable_unprepare(priv->clk);
out_put_node:
	of_node_put(phy_node);

	return err;
}