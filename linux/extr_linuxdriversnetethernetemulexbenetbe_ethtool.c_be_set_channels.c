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
struct net_device {int dummy; } ;
struct ethtool_channels {scalar_t__ combined_count; scalar_t__ rx_count; scalar_t__ tx_count; scalar_t__ other_count; } ;
struct be_adapter {scalar_t__ cfg_num_rx_irqs; scalar_t__ cfg_num_tx_irqs; } ;

/* Variables and functions */
 int EINVAL ; 
 int be_cmd_status (int) ; 
 scalar_t__ be_max_qp_irqs (struct be_adapter*) ; 
 scalar_t__ be_max_rx_irqs (struct be_adapter*) ; 
 scalar_t__ be_max_tx_irqs (struct be_adapter*) ; 
 int be_update_queues (struct be_adapter*) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int be_set_channels(struct net_device  *netdev,
			   struct ethtool_channels *ch)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	int status;

	/* we support either only combined channels or a combination of
	 * combined and either RX-only or TX-only channels.
	 */
	if (ch->other_count || !ch->combined_count ||
	    (ch->rx_count && ch->tx_count))
		return -EINVAL;

	if (ch->combined_count > be_max_qp_irqs(adapter) ||
	    (ch->rx_count &&
	     (ch->rx_count + ch->combined_count) > be_max_rx_irqs(adapter)) ||
	    (ch->tx_count &&
	     (ch->tx_count + ch->combined_count) > be_max_tx_irqs(adapter)))
		return -EINVAL;

	adapter->cfg_num_rx_irqs = ch->combined_count + ch->rx_count;
	adapter->cfg_num_tx_irqs = ch->combined_count + ch->tx_count;

	status = be_update_queues(adapter);
	return be_cmd_status(status);
}