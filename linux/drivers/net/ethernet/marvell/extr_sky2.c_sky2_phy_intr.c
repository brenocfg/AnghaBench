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
typedef  int u16 ;
struct sky2_port {int /*<<< orphan*/  phy_lock; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  netdev; } ;
struct sky2_hw {struct net_device** dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  PHY_MARV_INT_STAT ; 
 int /*<<< orphan*/  PHY_MARV_PHY_STAT ; 
 int PHY_M_IS_AN_COMPL ; 
 int PHY_M_IS_DUP_CHANGE ; 
 int PHY_M_IS_LSP_CHANGE ; 
 int PHY_M_IS_LST_CHANGE ; 
 int PHY_M_PS_FULL_DUP ; 
 int PHY_M_PS_LINK_UP ; 
 int gm_phy_read (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct sky2_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 scalar_t__ sky2_autoneg_done (struct sky2_port*,int) ; 
 int /*<<< orphan*/  sky2_link_down (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_link_up (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_phy_speed (struct sky2_hw*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sky2_phy_intr(struct sky2_hw *hw, unsigned port)
{
	struct net_device *dev = hw->dev[port];
	struct sky2_port *sky2 = netdev_priv(dev);
	u16 istatus, phystat;

	if (!netif_running(dev))
		return;

	spin_lock(&sky2->phy_lock);
	istatus = gm_phy_read(hw, port, PHY_MARV_INT_STAT);
	phystat = gm_phy_read(hw, port, PHY_MARV_PHY_STAT);

	netif_info(sky2, intr, sky2->netdev, "phy interrupt status 0x%x 0x%x\n",
		   istatus, phystat);

	if (istatus & PHY_M_IS_AN_COMPL) {
		if (sky2_autoneg_done(sky2, phystat) == 0 &&
		    !netif_carrier_ok(dev))
			sky2_link_up(sky2);
		goto out;
	}

	if (istatus & PHY_M_IS_LSP_CHANGE)
		sky2->speed = sky2_phy_speed(hw, phystat);

	if (istatus & PHY_M_IS_DUP_CHANGE)
		sky2->duplex =
		    (phystat & PHY_M_PS_FULL_DUP) ? DUPLEX_FULL : DUPLEX_HALF;

	if (istatus & PHY_M_IS_LST_CHANGE) {
		if (phystat & PHY_M_PS_LINK_UP)
			sky2_link_up(sky2);
		else
			sky2_link_down(sky2);
	}
out:
	spin_unlock(&sky2->phy_lock);
}