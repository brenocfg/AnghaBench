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
typedef  int /*<<< orphan*/  u16 ;
struct ksz_port {int first_port; int port_cnt; int speed; int duplex; struct ksz_hw* hw; } ;
struct ksz_hw {int dummy; } ;

/* Variables and functions */
 int KS884X_PHY_1_CTRL_OFFSET ; 
 int /*<<< orphan*/  PHY_AUTO_NEG_ENABLE ; 
 int PHY_CTRL_INTERVAL ; 
 int /*<<< orphan*/  PHY_FULL_DUPLEX ; 
 int /*<<< orphan*/  PHY_SPEED_100MBIT ; 
 int /*<<< orphan*/  hw_r_phy_ctrl (struct ksz_hw*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_w_phy_ctrl (struct ksz_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void port_force_link_speed(struct ksz_port *port)
{
	struct ksz_hw *hw = port->hw;
	u16 data;
	int i;
	int phy;
	int p;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		phy = KS884X_PHY_1_CTRL_OFFSET + p * PHY_CTRL_INTERVAL;
		hw_r_phy_ctrl(hw, phy, &data);

		data &= ~PHY_AUTO_NEG_ENABLE;

		if (10 == port->speed)
			data &= ~PHY_SPEED_100MBIT;
		else if (100 == port->speed)
			data |= PHY_SPEED_100MBIT;
		if (1 == port->duplex)
			data &= ~PHY_FULL_DUPLEX;
		else if (2 == port->duplex)
			data |= PHY_FULL_DUPLEX;
		hw_w_phy_ctrl(hw, phy, data);
	}
}