#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {struct device_node* of_node; struct bcmgenet_platform_data* platform_data; } ;
struct platform_device {TYPE_3__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct net_device {int watchdog_timeo; int hw_features; int needed_headroom; int /*<<< orphan*/  name; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  dev_addr; } ;
struct device_node {int dummy; } ;
struct bcmgenet_priv {void const* base; int wol_irq_disabled; int version; void const* clk; void const* clk_wol; void const* clk_eee; TYPE_2__* rx_rings; TYPE_1__* hw_params; struct net_device* dev; struct platform_device* pdev; int /*<<< orphan*/  bcmgenet_irq_work; int /*<<< orphan*/  rx_buf_len; int /*<<< orphan*/  wq; void* wol_irq; int /*<<< orphan*/  msg_enable; int /*<<< orphan*/  lock; void* irq1; void* irq0; } ;
struct bcmgenet_platform_data {void* mac_address; int genet_version; } ;
typedef  enum bcmgenet_version { ____Placeholder_bcmgenet_version } bcmgenet_version ;
struct TYPE_11__ {int rx_max_coalesced_frames; } ;
struct TYPE_10__ {int rx_queues; scalar_t__ tx_queues; } ;

/* Variables and functions */
 size_t DESC_INDEX ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ GENET_MAX_MQ_CNT ; 
 int /*<<< orphan*/  GENET_MSG_DEFAULT ; 
 int /*<<< orphan*/  GENET_POWER_PASSIVE ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void const*) ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int PTR_ERR (void const*) ; 
 int /*<<< orphan*/  RX_BUF_LENGTH ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_3__*) ; 
 struct net_device* alloc_etherdev_mqs (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bcmgenet_ethtool_ops ; 
 int /*<<< orphan*/  bcmgenet_irq_task ; 
 int /*<<< orphan*/  bcmgenet_match ; 
 int bcmgenet_mii_init (struct net_device*) ; 
 int /*<<< orphan*/  bcmgenet_netdev_ops ; 
 int /*<<< orphan*/  bcmgenet_power_up (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_set_hw_params (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_wol_isr ; 
 int /*<<< orphan*/  clk_disable_unprepare (void const*) ; 
 int /*<<< orphan*/  clk_prepare_enable (void const*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_3__*,struct net_device*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (TYPE_3__*,int) ; 
 void* devm_clk_get (TYPE_3__*,char*) ; 
 void const* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_boot_setup_check (struct net_device*) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_init (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_real_num_rx_queues (struct net_device*,int) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (struct net_device*,scalar_t__) ; 
 void* of_get_mac_address (struct device_node*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,char const**) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  reset_umac (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static int bcmgenet_probe(struct platform_device *pdev)
{
	struct bcmgenet_platform_data *pd = pdev->dev.platform_data;
	struct device_node *dn = pdev->dev.of_node;
	const struct of_device_id *of_id = NULL;
	struct bcmgenet_priv *priv;
	struct net_device *dev;
	const void *macaddr;
	unsigned int i;
	int err = -EIO;
	const char *phy_mode_str;

	/* Up to GENET_MAX_MQ_CNT + 1 TX queues and RX queues */
	dev = alloc_etherdev_mqs(sizeof(*priv), GENET_MAX_MQ_CNT + 1,
				 GENET_MAX_MQ_CNT + 1);
	if (!dev) {
		dev_err(&pdev->dev, "can't allocate net device\n");
		return -ENOMEM;
	}

	if (dn) {
		of_id = of_match_node(bcmgenet_match, dn);
		if (!of_id)
			return -EINVAL;
	}

	priv = netdev_priv(dev);
	priv->irq0 = platform_get_irq(pdev, 0);
	priv->irq1 = platform_get_irq(pdev, 1);
	priv->wol_irq = platform_get_irq(pdev, 2);
	if (!priv->irq0 || !priv->irq1) {
		dev_err(&pdev->dev, "can't find IRQs\n");
		err = -EINVAL;
		goto err;
	}

	if (dn) {
		macaddr = of_get_mac_address(dn);
		if (IS_ERR(macaddr)) {
			dev_err(&pdev->dev, "can't find MAC address\n");
			err = -EINVAL;
			goto err;
		}
	} else {
		macaddr = pd->mac_address;
	}

	priv->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->base)) {
		err = PTR_ERR(priv->base);
		goto err;
	}

	spin_lock_init(&priv->lock);

	SET_NETDEV_DEV(dev, &pdev->dev);
	dev_set_drvdata(&pdev->dev, dev);
	ether_addr_copy(dev->dev_addr, macaddr);
	dev->watchdog_timeo = 2 * HZ;
	dev->ethtool_ops = &bcmgenet_ethtool_ops;
	dev->netdev_ops = &bcmgenet_netdev_ops;

	priv->msg_enable = netif_msg_init(-1, GENET_MSG_DEFAULT);

	/* Set hardware features */
	dev->hw_features |= NETIF_F_SG | NETIF_F_IP_CSUM |
		NETIF_F_IPV6_CSUM | NETIF_F_RXCSUM;

	/* Request the WOL interrupt and advertise suspend if available */
	priv->wol_irq_disabled = true;
	err = devm_request_irq(&pdev->dev, priv->wol_irq, bcmgenet_wol_isr, 0,
			       dev->name, priv);
	if (!err)
		device_set_wakeup_capable(&pdev->dev, 1);

	/* Set the needed headroom to account for any possible
	 * features enabling/disabling at runtime
	 */
	dev->needed_headroom += 64;

	netdev_boot_setup_check(dev);

	priv->dev = dev;
	priv->pdev = pdev;
	if (of_id)
		priv->version = (enum bcmgenet_version)of_id->data;
	else
		priv->version = pd->genet_version;

	priv->clk = devm_clk_get(&priv->pdev->dev, "enet");
	if (IS_ERR(priv->clk)) {
		dev_warn(&priv->pdev->dev, "failed to get enet clock\n");
		priv->clk = NULL;
	}

	clk_prepare_enable(priv->clk);

	bcmgenet_set_hw_params(priv);

	/* Mii wait queue */
	init_waitqueue_head(&priv->wq);
	/* Always use RX_BUF_LENGTH (2KB) buffer for all chips */
	priv->rx_buf_len = RX_BUF_LENGTH;
	INIT_WORK(&priv->bcmgenet_irq_work, bcmgenet_irq_task);

	priv->clk_wol = devm_clk_get(&priv->pdev->dev, "enet-wol");
	if (IS_ERR(priv->clk_wol)) {
		dev_warn(&priv->pdev->dev, "failed to get enet-wol clock\n");
		priv->clk_wol = NULL;
	}

	priv->clk_eee = devm_clk_get(&priv->pdev->dev, "enet-eee");
	if (IS_ERR(priv->clk_eee)) {
		dev_warn(&priv->pdev->dev, "failed to get enet-eee clock\n");
		priv->clk_eee = NULL;
	}

	/* If this is an internal GPHY, power it on now, before UniMAC is
	 * brought out of reset as absolutely no UniMAC activity is allowed
	 */
	if (dn && !of_property_read_string(dn, "phy-mode", &phy_mode_str) &&
	    !strcasecmp(phy_mode_str, "internal"))
		bcmgenet_power_up(priv, GENET_POWER_PASSIVE);

	reset_umac(priv);

	err = bcmgenet_mii_init(dev);
	if (err)
		goto err_clk_disable;

	/* setup number of real queues  + 1 (GENET_V1 has 0 hardware queues
	 * just the ring 16 descriptor based TX
	 */
	netif_set_real_num_tx_queues(priv->dev, priv->hw_params->tx_queues + 1);
	netif_set_real_num_rx_queues(priv->dev, priv->hw_params->rx_queues + 1);

	/* Set default coalescing parameters */
	for (i = 0; i < priv->hw_params->rx_queues; i++)
		priv->rx_rings[i].rx_max_coalesced_frames = 1;
	priv->rx_rings[DESC_INDEX].rx_max_coalesced_frames = 1;

	/* libphy will determine the link state */
	netif_carrier_off(dev);

	/* Turn off the main clock, WOL clock is handled separately */
	clk_disable_unprepare(priv->clk);

	err = register_netdev(dev);
	if (err)
		goto err;

	return err;

err_clk_disable:
	clk_disable_unprepare(priv->clk);
err:
	free_netdev(dev);
	return err;
}