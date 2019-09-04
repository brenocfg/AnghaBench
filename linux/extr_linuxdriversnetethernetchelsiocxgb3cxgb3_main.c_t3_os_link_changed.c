#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ops; } ;
struct cmac {scalar_t__ offset; } ;
struct port_info {int /*<<< orphan*/  link_config; TYPE_2__ phy; struct cmac mac; int /*<<< orphan*/  port_id; } ;
struct net_device {int dummy; } ;
struct adapter {struct net_device** port; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* power_down ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 scalar_t__ A_XGM_INT_CAUSE ; 
 scalar_t__ A_XGM_INT_ENABLE ; 
 scalar_t__ A_XGM_INT_STATUS ; 
 int /*<<< orphan*/  F_XGM_INT ; 
 int /*<<< orphan*/  MAC_DIRECTION_RX ; 
 int /*<<< orphan*/  disable_tx_fifo_drain (struct adapter*,struct port_info*) ; 
 int /*<<< orphan*/  enable_tx_fifo_drain (struct adapter*,struct port_info*) ; 
 scalar_t__ is_10G (struct adapter*) ; 
 int /*<<< orphan*/  link_report (struct net_device*) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  t3_link_start (TYPE_2__*,struct cmac*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_mac_disable (struct cmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_mac_enable (struct cmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_read_reg (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_xgm_intr_disable (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_xgm_intr_enable (struct adapter*,int /*<<< orphan*/ ) ; 

void t3_os_link_changed(struct adapter *adapter, int port_id, int link_stat,
			int speed, int duplex, int pause)
{
	struct net_device *dev = adapter->port[port_id];
	struct port_info *pi = netdev_priv(dev);
	struct cmac *mac = &pi->mac;

	/* Skip changes from disabled ports. */
	if (!netif_running(dev))
		return;

	if (link_stat != netif_carrier_ok(dev)) {
		if (link_stat) {
			disable_tx_fifo_drain(adapter, pi);

			t3_mac_enable(mac, MAC_DIRECTION_RX);

			/* Clear local faults */
			t3_xgm_intr_disable(adapter, pi->port_id);
			t3_read_reg(adapter, A_XGM_INT_STATUS +
				    pi->mac.offset);
			t3_write_reg(adapter,
				     A_XGM_INT_CAUSE + pi->mac.offset,
				     F_XGM_INT);

			t3_set_reg_field(adapter,
					 A_XGM_INT_ENABLE + pi->mac.offset,
					 F_XGM_INT, F_XGM_INT);
			t3_xgm_intr_enable(adapter, pi->port_id);

			netif_carrier_on(dev);
		} else {
			netif_carrier_off(dev);

			t3_xgm_intr_disable(adapter, pi->port_id);
			t3_read_reg(adapter, A_XGM_INT_STATUS + pi->mac.offset);
			t3_set_reg_field(adapter,
					 A_XGM_INT_ENABLE + pi->mac.offset,
					 F_XGM_INT, 0);

			if (is_10G(adapter))
				pi->phy.ops->power_down(&pi->phy, 1);

			t3_read_reg(adapter, A_XGM_INT_STATUS + pi->mac.offset);
			t3_mac_disable(mac, MAC_DIRECTION_RX);
			t3_link_start(&pi->phy, mac, &pi->link_config);

			/* Flush TX FIFO */
			enable_tx_fifo_drain(adapter, pi);
		}

		link_report(dev);
	}
}