#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct net_device {int watchdog_timeo; int features; int vlan_features; int hw_features; int min_mtu; int max_mtu; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  gso_max_segs; int /*<<< orphan*/  priv_flags; scalar_t__ base_addr; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  irq; int /*<<< orphan*/ * ethtool_ops; } ;
struct TYPE_9__ {scalar_t__ expires; } ;
struct mv643xx_eth_private {int port_num; int t_clk; scalar_t__ tx_desc_sram_size; struct phy_device* clk; TYPE_3__* shared; TYPE_2__ rx_oom; int /*<<< orphan*/  napi; int /*<<< orphan*/  tx_timeout_task; int /*<<< orphan*/  mib_counters_lock; TYPE_2__ mib_counters_timer; struct net_device* dev; int /*<<< orphan*/  rxq_count; int /*<<< orphan*/  txq_count; scalar_t__ base; } ;
struct mv643xx_eth_platform_data {int port_number; scalar_t__ phy_addr; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; scalar_t__ phy_node; int /*<<< orphan*/ * shared; } ;
struct TYPE_10__ {scalar_t__ win_protect; struct phy_device* clk; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CLK125_BYPASS_EN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int HZ ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 scalar_t__ MV643XX_ETH_PHY_NONE ; 
 int /*<<< orphan*/  MV643XX_MAX_TSO_SEGS ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int PORT_SDMA_CONFIG_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PORT_SERIAL_CONTROL1 ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  SDMA_CONFIG ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_4__*) ; 
 int /*<<< orphan*/  WINDOW_PROTECT (int) ; 
 struct net_device* alloc_etherdev_mq (int,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct phy_device*) ; 
 void* clk_get_rate (struct phy_device*) ; 
 int /*<<< orphan*/  clk_prepare_enable (struct phy_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 struct mv643xx_eth_platform_data* dev_get_platdata (TYPE_4__*) ; 
 struct phy_device* devm_clk_get (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  get_phy_mode (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  init_pscr (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mib_counters_clear (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  mib_counters_timer_wrapper ; 
 int /*<<< orphan*/  mv643xx_eth_adjust_link ; 
 int /*<<< orphan*/  mv643xx_eth_ethtool_ops ; 
 int /*<<< orphan*/  mv643xx_eth_netdev_ops ; 
 int /*<<< orphan*/  mv643xx_eth_poll ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*,...) ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 struct phy_device* of_phy_connect (struct net_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oom_timer_wrapper ; 
 int /*<<< orphan*/  phy_addr_set (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_init (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_scan (struct mv643xx_eth_private*,scalar_t__) ; 
 TYPE_3__* platform_get_drvdata (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mv643xx_eth_private*) ; 
 int rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  set_params (struct mv643xx_eth_private*,struct mv643xx_eth_platform_data*) ; 
 int /*<<< orphan*/  set_rx_coal (struct mv643xx_eth_private*,int) ; 
 int /*<<< orphan*/  set_tx_coal (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_timeout_task ; 
 int /*<<< orphan*/  wrl (struct mv643xx_eth_private*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv643xx_eth_probe(struct platform_device *pdev)
{
	struct mv643xx_eth_platform_data *pd;
	struct mv643xx_eth_private *mp;
	struct net_device *dev;
	struct phy_device *phydev = NULL;
	struct resource *res;
	int err;

	pd = dev_get_platdata(&pdev->dev);
	if (pd == NULL) {
		dev_err(&pdev->dev, "no mv643xx_eth_platform_data\n");
		return -ENODEV;
	}

	if (pd->shared == NULL) {
		dev_err(&pdev->dev, "no mv643xx_eth_platform_data->shared\n");
		return -ENODEV;
	}

	dev = alloc_etherdev_mq(sizeof(struct mv643xx_eth_private), 8);
	if (!dev)
		return -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);
	mp = netdev_priv(dev);
	platform_set_drvdata(pdev, mp);

	mp->shared = platform_get_drvdata(pd->shared);
	mp->base = mp->shared->base + 0x0400 + (pd->port_number << 10);
	mp->port_num = pd->port_number;

	mp->dev = dev;

	/* Kirkwood resets some registers on gated clocks. Especially
	 * CLK125_BYPASS_EN must be cleared but is not available on
	 * all other SoCs/System Controllers using this driver.
	 */
	if (of_device_is_compatible(pdev->dev.of_node,
				    "marvell,kirkwood-eth-port"))
		wrlp(mp, PORT_SERIAL_CONTROL1,
		     rdlp(mp, PORT_SERIAL_CONTROL1) & ~CLK125_BYPASS_EN);

	/*
	 * Start with a default rate, and if there is a clock, allow
	 * it to override the default.
	 */
	mp->t_clk = 133000000;
	mp->clk = devm_clk_get(&pdev->dev, NULL);
	if (!IS_ERR(mp->clk)) {
		clk_prepare_enable(mp->clk);
		mp->t_clk = clk_get_rate(mp->clk);
	} else if (!IS_ERR(mp->shared->clk)) {
		mp->t_clk = clk_get_rate(mp->shared->clk);
	}

	set_params(mp, pd);
	netif_set_real_num_tx_queues(dev, mp->txq_count);
	netif_set_real_num_rx_queues(dev, mp->rxq_count);

	err = 0;
	if (pd->phy_node) {
		phydev = of_phy_connect(mp->dev, pd->phy_node,
					mv643xx_eth_adjust_link, 0,
					get_phy_mode(mp));
		if (!phydev)
			err = -ENODEV;
		else
			phy_addr_set(mp, phydev->mdio.addr);
	} else if (pd->phy_addr != MV643XX_ETH_PHY_NONE) {
		phydev = phy_scan(mp, pd->phy_addr);

		if (IS_ERR(phydev))
			err = PTR_ERR(phydev);
		else
			phy_init(mp, pd->speed, pd->duplex);
	}
	if (err == -ENODEV) {
		err = -EPROBE_DEFER;
		goto out;
	}
	if (err)
		goto out;

	dev->ethtool_ops = &mv643xx_eth_ethtool_ops;

	init_pscr(mp, pd->speed, pd->duplex);


	mib_counters_clear(mp);

	timer_setup(&mp->mib_counters_timer, mib_counters_timer_wrapper, 0);
	mp->mib_counters_timer.expires = jiffies + 30 * HZ;

	spin_lock_init(&mp->mib_counters_lock);

	INIT_WORK(&mp->tx_timeout_task, tx_timeout_task);

	netif_napi_add(dev, &mp->napi, mv643xx_eth_poll, NAPI_POLL_WEIGHT);

	timer_setup(&mp->rx_oom, oom_timer_wrapper, 0);


	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	BUG_ON(!res);
	dev->irq = res->start;

	dev->netdev_ops = &mv643xx_eth_netdev_ops;

	dev->watchdog_timeo = 2 * HZ;
	dev->base_addr = 0;

	dev->features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO;
	dev->vlan_features = dev->features;

	dev->features |= NETIF_F_RXCSUM;
	dev->hw_features = dev->features;

	dev->priv_flags |= IFF_UNICAST_FLT;
	dev->gso_max_segs = MV643XX_MAX_TSO_SEGS;

	/* MTU range: 64 - 9500 */
	dev->min_mtu = 64;
	dev->max_mtu = 9500;

	if (mp->shared->win_protect)
		wrl(mp, WINDOW_PROTECT(mp->port_num), mp->shared->win_protect);

	netif_carrier_off(dev);

	wrlp(mp, SDMA_CONFIG, PORT_SDMA_CONFIG_DEFAULT_VALUE);

	set_rx_coal(mp, 250);
	set_tx_coal(mp, 0);

	err = register_netdev(dev);
	if (err)
		goto out;

	netdev_notice(dev, "port %d with MAC address %pM\n",
		      mp->port_num, dev->dev_addr);

	if (mp->tx_desc_sram_size > 0)
		netdev_notice(dev, "configured with sram\n");

	return 0;

out:
	if (!IS_ERR(mp->clk))
		clk_disable_unprepare(mp->clk);
	free_netdev(dev);

	return err;
}