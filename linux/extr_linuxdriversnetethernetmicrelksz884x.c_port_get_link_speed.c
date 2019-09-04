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
typedef  int /*<<< orphan*/  uint ;
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct ksz_port_info {scalar_t__ advertised; scalar_t__ partner; int tx_rate; int duplex; scalar_t__ state; } ;
struct ksz_port {int first_port; int port_cnt; struct ksz_port_info* linked; struct ksz_hw* hw; } ;
struct ksz_hw {TYPE_1__* port_mib; scalar_t__ ksz_switch; struct ksz_port_info* port_info; } ;
struct TYPE_2__ {int link_down; scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS884X_PHY_AUTO_NEG_OFFSET ; 
 int /*<<< orphan*/  KS884X_PHY_REMOTE_CAP_OFFSET ; 
 int /*<<< orphan*/  KS884X_PORT_CTRL_4_OFFSET ; 
 int /*<<< orphan*/  KS884X_PORT_STATUS_OFFSET ; 
 int PORT_AUTO_NEG_COMPLETE ; 
 int PORT_STATUS_FULL_DUPLEX ; 
 int PORT_STATUS_LINK_GOOD ; 
 int PORT_STATUS_SPEED_100MBIT ; 
 int TX_RATE_UNIT ; 
 int /*<<< orphan*/  determine_flow_ctrl (struct ksz_hw*,struct ksz_port*,int,int) ; 
 int /*<<< orphan*/  hw_block_intr (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_r_phy (struct ksz_hw*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hw_restore_intr (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ media_connected ; 
 scalar_t__ media_disconnected ; 
 int /*<<< orphan*/  port_cfg_back_pressure (struct ksz_hw*,int,int) ; 
 int /*<<< orphan*/  port_cfg_change (struct ksz_hw*,struct ksz_port*,struct ksz_port_info*,int) ; 
 int /*<<< orphan*/  port_r16 (struct ksz_hw*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void port_get_link_speed(struct ksz_port *port)
{
	uint interrupt;
	struct ksz_port_info *info;
	struct ksz_port_info *linked = NULL;
	struct ksz_hw *hw = port->hw;
	u16 data;
	u16 status;
	u8 local;
	u8 remote;
	int i;
	int p;
	int change = 0;

	interrupt = hw_block_intr(hw);

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		info = &hw->port_info[p];
		port_r16(hw, p, KS884X_PORT_CTRL_4_OFFSET, &data);
		port_r16(hw, p, KS884X_PORT_STATUS_OFFSET, &status);

		/*
		 * Link status is changing all the time even when there is no
		 * cable connection!
		 */
		remote = status & (PORT_AUTO_NEG_COMPLETE |
			PORT_STATUS_LINK_GOOD);
		local = (u8) data;

		/* No change to status. */
		if (local == info->advertised && remote == info->partner)
			continue;

		info->advertised = local;
		info->partner = remote;
		if (status & PORT_STATUS_LINK_GOOD) {

			/* Remember the first linked port. */
			if (!linked)
				linked = info;

			info->tx_rate = 10 * TX_RATE_UNIT;
			if (status & PORT_STATUS_SPEED_100MBIT)
				info->tx_rate = 100 * TX_RATE_UNIT;

			info->duplex = 1;
			if (status & PORT_STATUS_FULL_DUPLEX)
				info->duplex = 2;

			if (media_connected != info->state) {
				hw_r_phy(hw, p, KS884X_PHY_AUTO_NEG_OFFSET,
					&data);
				hw_r_phy(hw, p, KS884X_PHY_REMOTE_CAP_OFFSET,
					&status);
				determine_flow_ctrl(hw, port, data, status);
				if (hw->ksz_switch) {
					port_cfg_back_pressure(hw, p,
						(1 == info->duplex));
				}
				change |= 1 << i;
				port_cfg_change(hw, port, info, status);
			}
			info->state = media_connected;
		} else {
			if (media_disconnected != info->state) {
				change |= 1 << i;

				/* Indicate the link just goes down. */
				hw->port_mib[p].link_down = 1;
			}
			info->state = media_disconnected;
		}
		hw->port_mib[p].state = (u8) info->state;
	}

	if (linked && media_disconnected == port->linked->state)
		port->linked = linked;

	hw_restore_intr(hw, interrupt);
}