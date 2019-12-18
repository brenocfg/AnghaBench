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
typedef  int u8 ;
struct tc_mqprio_qopt {int num_tc; int /*<<< orphan*/  hw; } ;
struct net_device {int num_tc; } ;
struct dpaa2_eth_priv {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TC_MQPRIO_HW_OFFLOAD_TCS ; 
 int TC_SETUP_QDISC_MQPRIO ; 
 int dpaa2_eth_queue_count (struct dpaa2_eth_priv*) ; 
 int dpaa2_eth_tc_count (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_reset_tc (struct net_device*) ; 
 int /*<<< orphan*/  netdev_set_num_tc (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_set_tc_queue (struct net_device*,int,int,int) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (struct net_device*,int) ; 
 int /*<<< orphan*/  update_xps (struct dpaa2_eth_priv*) ; 

__attribute__((used)) static int dpaa2_eth_setup_tc(struct net_device *net_dev,
			      enum tc_setup_type type, void *type_data)
{
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	struct tc_mqprio_qopt *mqprio = type_data;
	u8 num_tc, num_queues;
	int i;

	if (type != TC_SETUP_QDISC_MQPRIO)
		return -EINVAL;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;
	num_queues = dpaa2_eth_queue_count(priv);
	num_tc = mqprio->num_tc;

	if (num_tc == net_dev->num_tc)
		return 0;

	if (num_tc  > dpaa2_eth_tc_count(priv)) {
		netdev_err(net_dev, "Max %d traffic classes supported\n",
			   dpaa2_eth_tc_count(priv));
		return -EINVAL;
	}

	if (!num_tc) {
		netdev_reset_tc(net_dev);
		netif_set_real_num_tx_queues(net_dev, num_queues);
		goto out;
	}

	netdev_set_num_tc(net_dev, num_tc);
	netif_set_real_num_tx_queues(net_dev, num_tc * num_queues);

	for (i = 0; i < num_tc; i++)
		netdev_set_tc_queue(net_dev, i, num_queues, i * num_queues);

out:
	update_xps(priv);

	return 0;
}