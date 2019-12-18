#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev_addr; } ;
struct ksz_port {int first_port; } ;
struct ksz_hw {int dev_count; int features; int /*<<< orphan*/  tx_desc_info; int /*<<< orphan*/  rx_desc_info; int /*<<< orphan*/  promiscuous; int /*<<< orphan*/  all_multi; TYPE_1__* ksz_switch; } ;
struct dev_priv {scalar_t__ promiscuous; scalar_t__ multicast; int /*<<< orphan*/  monitor_timer_info; struct ksz_port port; struct dev_info* adapter; } ;
struct dev_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_tasklet; int /*<<< orphan*/  rx_tasklet; int /*<<< orphan*/  mib_read; int /*<<< orphan*/  mib_timer_info; int /*<<< orphan*/  opened; int /*<<< orphan*/  wol_enable; struct ksz_hw hw; } ;
struct TYPE_2__ {int member; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  STP_STATE_DISABLED ; 
 int STP_SUPPORT ; 
 int /*<<< orphan*/  bridge_change (struct ksz_hw*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_clr_multicast (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_del_addr (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_dis_intr (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_disable (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_reset_pkts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksz_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  port_set_power_saving (struct ksz_port*,int) ; 
 int /*<<< orphan*/  port_set_stp_state (struct ksz_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_clr_sta_mac_table (struct ksz_hw*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transmit_cleanup (struct dev_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netdev_close(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_port *port = &priv->port;
	struct ksz_hw *hw = &hw_priv->hw;
	int pi;

	netif_stop_queue(dev);

	ksz_stop_timer(&priv->monitor_timer_info);

	/* Need to shut the port manually in multiple device interfaces mode. */
	if (hw->dev_count > 1) {
		port_set_stp_state(hw, port->first_port, STP_STATE_DISABLED);

		/* Port is closed.  Need to change bridge setting. */
		if (hw->features & STP_SUPPORT) {
			pi = 1 << port->first_port;
			if (hw->ksz_switch->member & pi) {
				hw->ksz_switch->member &= ~pi;
				bridge_change(hw);
			}
		}
	}
	if (port->first_port > 0)
		hw_del_addr(hw, dev->dev_addr);
	if (!hw_priv->wol_enable)
		port_set_power_saving(port, true);

	if (priv->multicast)
		--hw->all_multi;
	if (priv->promiscuous)
		--hw->promiscuous;

	hw_priv->opened--;
	if (!(hw_priv->opened)) {
		ksz_stop_timer(&hw_priv->mib_timer_info);
		flush_work(&hw_priv->mib_read);

		hw_dis_intr(hw);
		hw_disable(hw);
		hw_clr_multicast(hw);

		/* Delay for receive task to stop scheduling itself. */
		msleep(2000 / HZ);

		tasklet_kill(&hw_priv->rx_tasklet);
		tasklet_kill(&hw_priv->tx_tasklet);
		free_irq(dev->irq, hw_priv->dev);

		transmit_cleanup(hw_priv, 0);
		hw_reset_pkts(&hw->rx_desc_info);
		hw_reset_pkts(&hw->tx_desc_info);

		/* Clean out static MAC table when the switch is shutdown. */
		if (hw->features & STP_SUPPORT)
			sw_clr_sta_mac_table(hw);
	}

	return 0;
}