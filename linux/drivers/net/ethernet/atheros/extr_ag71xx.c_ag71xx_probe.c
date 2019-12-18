#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct resource {scalar_t__ start; } ;
struct TYPE_15__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct net_device {int min_mtu; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev_addr; scalar_t__ max_mtu; int /*<<< orphan*/ * netdev_ops; } ;
struct device_node {int dummy; } ;
struct ag71xx_desc {int dummy; } ;
struct ag71xx_dcfg {void const* fifodata; scalar_t__ max_frame_len; } ;
struct TYPE_14__ {void* order; int /*<<< orphan*/  desc_split; } ;
struct TYPE_13__ {void* order; } ;
struct ag71xx {int mac_idx; void const* clk_eth; void const* mac_reset; int phy_if_mode; scalar_t__ mac_base; int /*<<< orphan*/  napi; scalar_t__ stop_desc_dma; TYPE_4__* stop_desc; TYPE_2__ tx_ring; int /*<<< orphan*/  rx_buf_offset; TYPE_1__ rx_ring; int /*<<< orphan*/  oom_timer; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  fifodata; int /*<<< orphan*/  msg_enable; struct ag71xx_dcfg const* dcfg; struct net_device* ndev; struct platform_device* pdev; } ;
struct TYPE_16__ {scalar_t__ next; scalar_t__ ctrl; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_DEFAULT_MSG_ENABLE ; 
 int /*<<< orphan*/  AG71XX_NAPI_WEIGHT ; 
 int /*<<< orphan*/  AG71XX_REG_MAC_CFG1 ; 
 int AG71XX_RX_RING_SIZE_DEFAULT ; 
 int AG71XX_TX_RING_DS_PER_PKT ; 
 int AG71XX_TX_RING_SIZE_DEFAULT ; 
 int /*<<< orphan*/  AG71XX_TX_RING_SPLIT ; 
 int /*<<< orphan*/  AR7100 ; 
 int /*<<< orphan*/  AR9130 ; 
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void const*) ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  NET_SKB_PAD ; 
 int PTR_ERR (void const*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  ag71xx_hw_init (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_interrupt ; 
 scalar_t__ ag71xx_is (struct ag71xx*,int /*<<< orphan*/ ) ; 
 scalar_t__ ag71xx_max_frame_len (int /*<<< orphan*/ ) ; 
 int ag71xx_mdio_probe (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_mdio_remove (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_netdev_ops ; 
 int /*<<< orphan*/  ag71xx_oom_timer_handler ; 
 int /*<<< orphan*/  ag71xx_poll ; 
 int /*<<< orphan*/  ag71xx_restart_work_func ; 
 void* ag71xx_ring_size_order (int) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* ar71xx_addr_ar7100 ; 
 int /*<<< orphan*/  clk_disable_unprepare (void const*) ; 
 int clk_prepare_enable (void const*) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 struct net_device* devm_alloc_etherdev (TYPE_3__*,int) ; 
 void const* devm_clk_get (TYPE_3__*,char*) ; 
 scalar_t__ devm_ioremap_nocache (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct net_device*) ; 
 void const* devm_reset_control_get (TYPE_3__*,char*) ; 
 TYPE_4__* dmam_alloc_coherent (TYPE_3__*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 struct ag71xx* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ag71xx*,int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_info (struct ag71xx*,int /*<<< orphan*/ ,struct net_device*,char*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_msg_init (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ag71xx_dcfg* of_device_get_match_data (TYPE_3__*) ; 
 void* of_get_mac_address (struct device_node*) ; 
 int of_get_phy_mode (struct device_node*) ; 
 int /*<<< orphan*/  phy_modes (int) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  probe ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ag71xx_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	const struct ag71xx_dcfg *dcfg;
	struct net_device *ndev;
	struct resource *res;
	const void *mac_addr;
	int tx_size, err, i;
	struct ag71xx *ag;

	if (!np)
		return -ENODEV;

	ndev = devm_alloc_etherdev(&pdev->dev, sizeof(*ag));
	if (!ndev)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -EINVAL;

	dcfg = of_device_get_match_data(&pdev->dev);
	if (!dcfg)
		return -EINVAL;

	ag = netdev_priv(ndev);
	ag->mac_idx = -1;
	for (i = 0; i < ARRAY_SIZE(ar71xx_addr_ar7100); i++) {
		if (ar71xx_addr_ar7100[i] == res->start)
			ag->mac_idx = i;
	}

	if (ag->mac_idx < 0) {
		netif_err(ag, probe, ndev, "unknown mac idx\n");
		return -EINVAL;
	}

	ag->clk_eth = devm_clk_get(&pdev->dev, "eth");
	if (IS_ERR(ag->clk_eth)) {
		netif_err(ag, probe, ndev, "Failed to get eth clk.\n");
		return PTR_ERR(ag->clk_eth);
	}

	SET_NETDEV_DEV(ndev, &pdev->dev);

	ag->pdev = pdev;
	ag->ndev = ndev;
	ag->dcfg = dcfg;
	ag->msg_enable = netif_msg_init(-1, AG71XX_DEFAULT_MSG_ENABLE);
	memcpy(ag->fifodata, dcfg->fifodata, sizeof(ag->fifodata));

	ag->mac_reset = devm_reset_control_get(&pdev->dev, "mac");
	if (IS_ERR(ag->mac_reset)) {
		netif_err(ag, probe, ndev, "missing mac reset\n");
		err = PTR_ERR(ag->mac_reset);
		goto err_free;
	}

	ag->mac_base = devm_ioremap_nocache(&pdev->dev, res->start,
					    resource_size(res));
	if (!ag->mac_base) {
		err = -ENOMEM;
		goto err_free;
	}

	ndev->irq = platform_get_irq(pdev, 0);
	err = devm_request_irq(&pdev->dev, ndev->irq, ag71xx_interrupt,
			       0x0, dev_name(&pdev->dev), ndev);
	if (err) {
		netif_err(ag, probe, ndev, "unable to request IRQ %d\n",
			  ndev->irq);
		goto err_free;
	}

	ndev->netdev_ops = &ag71xx_netdev_ops;

	INIT_DELAYED_WORK(&ag->restart_work, ag71xx_restart_work_func);
	timer_setup(&ag->oom_timer, ag71xx_oom_timer_handler, 0);

	tx_size = AG71XX_TX_RING_SIZE_DEFAULT;
	ag->rx_ring.order = ag71xx_ring_size_order(AG71XX_RX_RING_SIZE_DEFAULT);

	ndev->min_mtu = 68;
	ndev->max_mtu = dcfg->max_frame_len - ag71xx_max_frame_len(0);

	ag->rx_buf_offset = NET_SKB_PAD;
	if (!ag71xx_is(ag, AR7100) && !ag71xx_is(ag, AR9130))
		ag->rx_buf_offset += NET_IP_ALIGN;

	if (ag71xx_is(ag, AR7100)) {
		ag->tx_ring.desc_split = AG71XX_TX_RING_SPLIT;
		tx_size *= AG71XX_TX_RING_DS_PER_PKT;
	}
	ag->tx_ring.order = ag71xx_ring_size_order(tx_size);

	ag->stop_desc = dmam_alloc_coherent(&pdev->dev,
					    sizeof(struct ag71xx_desc),
					    &ag->stop_desc_dma, GFP_KERNEL);
	if (!ag->stop_desc) {
		err = -ENOMEM;
		goto err_free;
	}

	ag->stop_desc->data = 0;
	ag->stop_desc->ctrl = 0;
	ag->stop_desc->next = (u32)ag->stop_desc_dma;

	mac_addr = of_get_mac_address(np);
	if (!IS_ERR(mac_addr))
		memcpy(ndev->dev_addr, mac_addr, ETH_ALEN);
	if (IS_ERR(mac_addr) || !is_valid_ether_addr(ndev->dev_addr)) {
		netif_err(ag, probe, ndev, "invalid MAC address, using random address\n");
		eth_random_addr(ndev->dev_addr);
	}

	ag->phy_if_mode = of_get_phy_mode(np);
	if (ag->phy_if_mode < 0) {
		netif_err(ag, probe, ndev, "missing phy-mode property in DT\n");
		err = ag->phy_if_mode;
		goto err_free;
	}

	netif_napi_add(ndev, &ag->napi, ag71xx_poll, AG71XX_NAPI_WEIGHT);

	err = clk_prepare_enable(ag->clk_eth);
	if (err) {
		netif_err(ag, probe, ndev, "Failed to enable eth clk.\n");
		goto err_free;
	}

	ag71xx_wr(ag, AG71XX_REG_MAC_CFG1, 0);

	ag71xx_hw_init(ag);

	err = ag71xx_mdio_probe(ag);
	if (err)
		goto err_put_clk;

	platform_set_drvdata(pdev, ndev);

	err = register_netdev(ndev);
	if (err) {
		netif_err(ag, probe, ndev, "unable to register net device\n");
		platform_set_drvdata(pdev, NULL);
		goto err_mdio_remove;
	}

	netif_info(ag, probe, ndev, "Atheros AG71xx at 0x%08lx, irq %d, mode:%s\n",
		   (unsigned long)ag->mac_base, ndev->irq,
		   phy_modes(ag->phy_if_mode));

	return 0;

err_mdio_remove:
	ag71xx_mdio_remove(ag);
err_put_clk:
	clk_disable_unprepare(ag->clk_eth);
err_free:
	free_netdev(ndev);
	return err;
}