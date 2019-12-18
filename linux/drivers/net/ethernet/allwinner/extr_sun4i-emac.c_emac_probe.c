#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct net_device {unsigned long base_addr; int irq; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;
struct emac_board_info {char const* clk; int emacrx_completed_flag; TYPE_1__* dev; scalar_t__ membase; void* phy_node; int /*<<< orphan*/  lock; int /*<<< orphan*/  msg_enable; struct platform_device* pdev; struct net_device* ndev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_DEFAULT_MSG_ENABLE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ IS_ERR (char const*) ; 
 int PTR_ERR (char const*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_1__*) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (char const*) ; 
 int clk_prepare_enable (char const*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 char const* devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emac_ethtool_ops ; 
 int /*<<< orphan*/  emac_netdev_ops ; 
 int /*<<< orphan*/  emac_powerup (struct net_device*) ; 
 int /*<<< orphan*/  emac_reset (struct emac_board_info*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct emac_board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* of_get_mac_address (struct device_node*) ; 
 scalar_t__ of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 void* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sunxi_sram_claim (TYPE_1__*) ; 
 int /*<<< orphan*/  sunxi_sram_release (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog ; 

__attribute__((used)) static int emac_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct emac_board_info *db;
	struct net_device *ndev;
	int ret = 0;
	const char *mac_addr;

	ndev = alloc_etherdev(sizeof(struct emac_board_info));
	if (!ndev) {
		dev_err(&pdev->dev, "could not allocate device.\n");
		return -ENOMEM;
	}

	SET_NETDEV_DEV(ndev, &pdev->dev);

	db = netdev_priv(ndev);

	db->dev = &pdev->dev;
	db->ndev = ndev;
	db->pdev = pdev;
	db->msg_enable = netif_msg_init(debug, EMAC_DEFAULT_MSG_ENABLE);

	spin_lock_init(&db->lock);

	db->membase = of_iomap(np, 0);
	if (!db->membase) {
		dev_err(&pdev->dev, "failed to remap registers\n");
		ret = -ENOMEM;
		goto out;
	}

	/* fill in parameters for net-dev structure */
	ndev->base_addr = (unsigned long)db->membase;
	ndev->irq = irq_of_parse_and_map(np, 0);
	if (ndev->irq == -ENXIO) {
		netdev_err(ndev, "No irq resource\n");
		ret = ndev->irq;
		goto out_iounmap;
	}

	db->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(db->clk)) {
		ret = PTR_ERR(db->clk);
		goto out_iounmap;
	}

	ret = clk_prepare_enable(db->clk);
	if (ret) {
		dev_err(&pdev->dev, "Error couldn't enable clock (%d)\n", ret);
		goto out_iounmap;
	}

	ret = sunxi_sram_claim(&pdev->dev);
	if (ret) {
		dev_err(&pdev->dev, "Error couldn't map SRAM to device\n");
		goto out_clk_disable_unprepare;
	}

	db->phy_node = of_parse_phandle(np, "phy-handle", 0);
	if (!db->phy_node)
		db->phy_node = of_parse_phandle(np, "phy", 0);
	if (!db->phy_node) {
		dev_err(&pdev->dev, "no associated PHY\n");
		ret = -ENODEV;
		goto out_release_sram;
	}

	/* Read MAC-address from DT */
	mac_addr = of_get_mac_address(np);
	if (!IS_ERR(mac_addr))
		ether_addr_copy(ndev->dev_addr, mac_addr);

	/* Check if the MAC address is valid, if not get a random one */
	if (!is_valid_ether_addr(ndev->dev_addr)) {
		eth_hw_addr_random(ndev);
		dev_warn(&pdev->dev, "using random MAC address %pM\n",
			 ndev->dev_addr);
	}

	db->emacrx_completed_flag = 1;
	emac_powerup(ndev);
	emac_reset(db);

	ndev->netdev_ops = &emac_netdev_ops;
	ndev->watchdog_timeo = msecs_to_jiffies(watchdog);
	ndev->ethtool_ops = &emac_ethtool_ops;

	platform_set_drvdata(pdev, ndev);

	/* Carrier starts down, phylib will bring it up */
	netif_carrier_off(ndev);

	ret = register_netdev(ndev);
	if (ret) {
		dev_err(&pdev->dev, "Registering netdev failed!\n");
		ret = -ENODEV;
		goto out_release_sram;
	}

	dev_info(&pdev->dev, "%s: at %p, IRQ %d MAC: %pM\n",
		 ndev->name, db->membase, ndev->irq, ndev->dev_addr);

	return 0;

out_release_sram:
	sunxi_sram_release(&pdev->dev);
out_clk_disable_unprepare:
	clk_disable_unprepare(db->clk);
out_iounmap:
	iounmap(db->membase);
out:
	dev_err(db->dev, "not found (%d).\n", ret);

	free_netdev(ndev);

	return ret;
}