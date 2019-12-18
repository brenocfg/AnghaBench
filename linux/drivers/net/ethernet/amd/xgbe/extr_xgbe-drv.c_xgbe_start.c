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
struct xgbe_phy_if {int (* phy_start ) (struct xgbe_prv_data*) ;} ;
struct xgbe_hw_if {int (* init ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* exit ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* enable_rx ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* enable_tx ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {unsigned int rx_ring_count; int /*<<< orphan*/  dev_state; int /*<<< orphan*/  service_work; int /*<<< orphan*/  dev_workqueue; int /*<<< orphan*/ * rss_table; int /*<<< orphan*/  tx_ring_count; struct net_device* netdev; struct xgbe_phy_if phy_if; struct xgbe_hw_if hw_if; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMCH ; 
 int /*<<< orphan*/  MAC_RSSDR ; 
 unsigned int XGBE_RSS_MAX_TABLE_SIZE ; 
 int /*<<< orphan*/  XGBE_STOPPED ; 
 int /*<<< orphan*/  XGMAC_SET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,unsigned int) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct xgbe_prv_data*) ; 
 int stub2 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub3 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub4 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub5 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  udp_tunnel_get_rx_info (struct net_device*) ; 
 int /*<<< orphan*/  xgbe_free_irqs (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_napi_disable (struct xgbe_prv_data*,int) ; 
 int /*<<< orphan*/  xgbe_napi_enable (struct xgbe_prv_data*,int) ; 
 int xgbe_request_irqs (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_start_timers (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_start(struct xgbe_prv_data *pdata)
{
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	struct xgbe_phy_if *phy_if = &pdata->phy_if;
	struct net_device *netdev = pdata->netdev;
	unsigned int i;
	int ret;

	/* Set the number of queues */
	ret = netif_set_real_num_tx_queues(netdev, pdata->tx_ring_count);
	if (ret) {
		netdev_err(netdev, "error setting real tx queue count\n");
		return ret;
	}

	ret = netif_set_real_num_rx_queues(netdev, pdata->rx_ring_count);
	if (ret) {
		netdev_err(netdev, "error setting real rx queue count\n");
		return ret;
	}

	/* Set RSS lookup table data for programming */
	for (i = 0; i < XGBE_RSS_MAX_TABLE_SIZE; i++)
		XGMAC_SET_BITS(pdata->rss_table[i], MAC_RSSDR, DMCH,
			       i % pdata->rx_ring_count);

	ret = hw_if->init(pdata);
	if (ret)
		return ret;

	xgbe_napi_enable(pdata, 1);

	ret = xgbe_request_irqs(pdata);
	if (ret)
		goto err_napi;

	ret = phy_if->phy_start(pdata);
	if (ret)
		goto err_irqs;

	hw_if->enable_tx(pdata);
	hw_if->enable_rx(pdata);

	udp_tunnel_get_rx_info(netdev);

	netif_tx_start_all_queues(netdev);

	xgbe_start_timers(pdata);
	queue_work(pdata->dev_workqueue, &pdata->service_work);

	clear_bit(XGBE_STOPPED, &pdata->dev_state);

	return 0;

err_irqs:
	xgbe_free_irqs(pdata);

err_napi:
	xgbe_napi_disable(pdata, 1);

	hw_if->exit(pdata);

	return ret;
}