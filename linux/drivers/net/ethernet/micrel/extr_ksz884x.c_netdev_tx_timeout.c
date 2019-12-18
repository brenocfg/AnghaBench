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
struct net_device {scalar_t__ watchdog_timeo; } ;
struct TYPE_4__ {int /*<<< orphan*/  ring_phys; } ;
struct ksz_hw {int dev_count; TYPE_1__* port_info; scalar_t__ multi_list_size; scalar_t__ all_multi; TYPE_2__ rx_desc_info; TYPE_2__ tx_desc_info; } ;
struct dev_priv {struct dev_info* adapter; } ;
struct dev_info {struct ksz_hw hw; } ;
struct TYPE_3__ {struct net_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  STP_STATE_DISABLED ; 
 int /*<<< orphan*/  STP_STATE_SIMPLE ; 
 int SWITCH_PORT_NUM ; 
 int /*<<< orphan*/  hw_dis_intr (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_disable (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_ena_intr (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_enable (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_reset (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_reset_pkts (TYPE_2__*) ; 
 int /*<<< orphan*/  hw_set_add_addr (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_set_addr (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_set_desc_base (struct ksz_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_set_grp_addr (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_set_multicast (struct ksz_hw*,scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  ksz_init_rx_buffers (struct dev_info*) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  port_set_stp_state (struct ksz_hw*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before_eq (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  transmit_cleanup (struct dev_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netdev_tx_timeout(struct net_device *dev)
{
	static unsigned long last_reset;

	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	int port;

	if (hw->dev_count > 1) {
		/*
		 * Only reset the hardware if time between calls is long
		 * enough.
		 */
		if (time_before_eq(jiffies, last_reset + dev->watchdog_timeo))
			hw_priv = NULL;
	}

	last_reset = jiffies;
	if (hw_priv) {
		hw_dis_intr(hw);
		hw_disable(hw);

		transmit_cleanup(hw_priv, 0);
		hw_reset_pkts(&hw->rx_desc_info);
		hw_reset_pkts(&hw->tx_desc_info);
		ksz_init_rx_buffers(hw_priv);

		hw_reset(hw);

		hw_set_desc_base(hw,
			hw->tx_desc_info.ring_phys,
			hw->rx_desc_info.ring_phys);
		hw_set_addr(hw);
		if (hw->all_multi)
			hw_set_multicast(hw, hw->all_multi);
		else if (hw->multi_list_size)
			hw_set_grp_addr(hw);

		if (hw->dev_count > 1) {
			hw_set_add_addr(hw);
			for (port = 0; port < SWITCH_PORT_NUM; port++) {
				struct net_device *port_dev;

				port_set_stp_state(hw, port,
					STP_STATE_DISABLED);

				port_dev = hw->port_info[port].pdev;
				if (netif_running(port_dev))
					port_set_stp_state(hw, port,
						STP_STATE_SIMPLE);
			}
		}

		hw_enable(hw);
		hw_ena_intr(hw);
	}

	netif_trans_update(dev);
	netif_wake_queue(dev);
}