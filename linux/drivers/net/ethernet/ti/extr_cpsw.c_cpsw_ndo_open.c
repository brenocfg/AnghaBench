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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {scalar_t__ rx_coalesce_usecs; } ;
struct TYPE_3__ {int /*<<< orphan*/  default_vlan; int /*<<< orphan*/  dual_emac; } ;
struct cpsw_priv {int tx_irq_disabled; int rx_irq_disabled; scalar_t__ coal_intvl; struct net_device* ndev; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma; int /*<<< orphan*/  usage_count; int /*<<< orphan*/  cpts; int /*<<< orphan*/ * irqs_table; int /*<<< orphan*/  napi_tx; int /*<<< orphan*/  napi_rx; TYPE_2__* regs; TYPE_1__ data; int /*<<< orphan*/  ale; int /*<<< orphan*/  version; int /*<<< orphan*/  rx_ch_num; int /*<<< orphan*/  tx_ch_num; struct cpsw_priv* cpsw; } ;
struct cpsw_common {int tx_irq_disabled; int rx_irq_disabled; scalar_t__ coal_intvl; struct net_device* ndev; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma; int /*<<< orphan*/  usage_count; int /*<<< orphan*/  cpts; int /*<<< orphan*/ * irqs_table; int /*<<< orphan*/  napi_tx; int /*<<< orphan*/  napi_rx; TYPE_2__* regs; TYPE_1__ data; int /*<<< orphan*/  ale; int /*<<< orphan*/  version; int /*<<< orphan*/  rx_ch_num; int /*<<< orphan*/  tx_ch_num; struct cpsw_common* cpsw; } ;
struct TYPE_4__ {int /*<<< orphan*/  flow_control; int /*<<< orphan*/  stat_port_en; int /*<<< orphan*/  ptype; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_ALL_PORTS ; 
 int /*<<< orphan*/  CPSW_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_MINOR_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_RTL_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpdma_ctlr_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpdma_ctlr_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_add_default_vlan (struct cpsw_priv*) ; 
 int /*<<< orphan*/  cpsw_ale_add_vlan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpsw_create_xdp_rxqs (struct cpsw_priv*) ; 
 int /*<<< orphan*/  cpsw_destroy_xdp_rxqs (struct cpsw_priv*) ; 
 int cpsw_fill_rx_channels (struct cpsw_priv*) ; 
 int /*<<< orphan*/  cpsw_init_host_port (struct cpsw_priv*) ; 
 int /*<<< orphan*/  cpsw_intr_enable (struct cpsw_priv*) ; 
 int /*<<< orphan*/  cpsw_restore (struct cpsw_priv*) ; 
 int /*<<< orphan*/  cpsw_set_coalesce (struct net_device*,struct ethtool_coalesce*) ; 
 int /*<<< orphan*/  cpsw_slave_open ; 
 int /*<<< orphan*/  cpsw_slave_stop ; 
 scalar_t__ cpts_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_slave (struct cpsw_priv*,int /*<<< orphan*/ ,struct cpsw_priv*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpsw_ndo_open(struct net_device *ndev)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;
	int ret;
	u32 reg;

	ret = pm_runtime_get_sync(cpsw->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(cpsw->dev);
		return ret;
	}

	netif_carrier_off(ndev);

	/* Notify the stack of the actual queue counts. */
	ret = netif_set_real_num_tx_queues(ndev, cpsw->tx_ch_num);
	if (ret) {
		dev_err(priv->dev, "cannot set real number of tx queues\n");
		goto err_cleanup;
	}

	ret = netif_set_real_num_rx_queues(ndev, cpsw->rx_ch_num);
	if (ret) {
		dev_err(priv->dev, "cannot set real number of rx queues\n");
		goto err_cleanup;
	}

	reg = cpsw->version;

	dev_info(priv->dev, "initializing cpsw version %d.%d (%d)\n",
		 CPSW_MAJOR_VERSION(reg), CPSW_MINOR_VERSION(reg),
		 CPSW_RTL_VERSION(reg));

	/* Initialize host and slave ports */
	if (!cpsw->usage_count)
		cpsw_init_host_port(priv);
	for_each_slave(priv, cpsw_slave_open, priv);

	/* Add default VLAN */
	if (!cpsw->data.dual_emac)
		cpsw_add_default_vlan(priv);
	else
		cpsw_ale_add_vlan(cpsw->ale, cpsw->data.default_vlan,
				  ALE_ALL_PORTS, ALE_ALL_PORTS, 0, 0);

	/* initialize shared resources for every ndev */
	if (!cpsw->usage_count) {
		/* disable priority elevation */
		writel_relaxed(0, &cpsw->regs->ptype);

		/* enable statistics collection only on all ports */
		writel_relaxed(0x7, &cpsw->regs->stat_port_en);

		/* Enable internal fifo flow control */
		writel(0x7, &cpsw->regs->flow_control);

		napi_enable(&cpsw->napi_rx);
		napi_enable(&cpsw->napi_tx);

		if (cpsw->tx_irq_disabled) {
			cpsw->tx_irq_disabled = false;
			enable_irq(cpsw->irqs_table[1]);
		}

		if (cpsw->rx_irq_disabled) {
			cpsw->rx_irq_disabled = false;
			enable_irq(cpsw->irqs_table[0]);
		}

		/* create rxqs for both infs in dual mac as they use same pool
		 * and must be destroyed together when no users.
		 */
		ret = cpsw_create_xdp_rxqs(cpsw);
		if (ret < 0)
			goto err_cleanup;

		ret = cpsw_fill_rx_channels(priv);
		if (ret < 0)
			goto err_cleanup;

		if (cpts_register(cpsw->cpts))
			dev_err(priv->dev, "error registering cpts device\n");

	}

	cpsw_restore(priv);

	/* Enable Interrupt pacing if configured */
	if (cpsw->coal_intvl != 0) {
		struct ethtool_coalesce coal;

		coal.rx_coalesce_usecs = cpsw->coal_intvl;
		cpsw_set_coalesce(ndev, &coal);
	}

	cpdma_ctlr_start(cpsw->dma);
	cpsw_intr_enable(cpsw);
	cpsw->usage_count++;

	return 0;

err_cleanup:
	if (!cpsw->usage_count) {
		cpdma_ctlr_stop(cpsw->dma);
		cpsw_destroy_xdp_rxqs(cpsw);
	}

	for_each_slave(priv, cpsw_slave_stop, cpsw);
	pm_runtime_put_sync(cpsw->dev);
	netif_carrier_off(priv->ndev);
	return ret;
}