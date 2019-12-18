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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ active_flowctrl; scalar_t__ active_speed; scalar_t__ active_duplex; int /*<<< orphan*/  flowctrl; } ;
struct tg3 {int mac_mode; scalar_t__ old_link; int /*<<< orphan*/  lock; TYPE_1__ link_config; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  mdio_bus; } ;
struct phy_device {scalar_t__ link; scalar_t__ speed; scalar_t__ duplex; scalar_t__ asym_pause; scalar_t__ pause; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5785 ; 
 scalar_t__ DUPLEX_HALF ; 
 int LPA_PAUSE_ASYM ; 
 int LPA_PAUSE_CAP ; 
 int /*<<< orphan*/  MAC_MI_STAT ; 
 int MAC_MI_STAT_10MBPS_MODE ; 
 int MAC_MI_STAT_LNKSTAT_ATTN_ENAB ; 
 int /*<<< orphan*/  MAC_MODE ; 
 int MAC_MODE_HALF_DUPLEX ; 
 int MAC_MODE_PORT_MODE_GMII ; 
 int MAC_MODE_PORT_MODE_MASK ; 
 int MAC_MODE_PORT_MODE_MII ; 
 int /*<<< orphan*/  MAC_TX_LENGTHS ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int TX_LENGTHS_IPG_CRS_SHIFT ; 
 int TX_LENGTHS_IPG_SHIFT ; 
 int TX_LENGTHS_SLOT_TIME_SHIFT ; 
 struct phy_device* mdiobus_get_phy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_advertise_flowctrl (int /*<<< orphan*/ ) ; 
 struct tg3* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 int /*<<< orphan*/  tg3_link_report (struct tg3*) ; 
 int /*<<< orphan*/  tg3_setup_flow_control (struct tg3*,int,int) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tg3_adjust_link(struct net_device *dev)
{
	u8 oldflowctrl, linkmesg = 0;
	u32 mac_mode, lcl_adv, rmt_adv;
	struct tg3 *tp = netdev_priv(dev);
	struct phy_device *phydev = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr);

	spin_lock_bh(&tp->lock);

	mac_mode = tp->mac_mode & ~(MAC_MODE_PORT_MODE_MASK |
				    MAC_MODE_HALF_DUPLEX);

	oldflowctrl = tp->link_config.active_flowctrl;

	if (phydev->link) {
		lcl_adv = 0;
		rmt_adv = 0;

		if (phydev->speed == SPEED_100 || phydev->speed == SPEED_10)
			mac_mode |= MAC_MODE_PORT_MODE_MII;
		else if (phydev->speed == SPEED_1000 ||
			 tg3_asic_rev(tp) != ASIC_REV_5785)
			mac_mode |= MAC_MODE_PORT_MODE_GMII;
		else
			mac_mode |= MAC_MODE_PORT_MODE_MII;

		if (phydev->duplex == DUPLEX_HALF)
			mac_mode |= MAC_MODE_HALF_DUPLEX;
		else {
			lcl_adv = mii_advertise_flowctrl(
				  tp->link_config.flowctrl);

			if (phydev->pause)
				rmt_adv = LPA_PAUSE_CAP;
			if (phydev->asym_pause)
				rmt_adv |= LPA_PAUSE_ASYM;
		}

		tg3_setup_flow_control(tp, lcl_adv, rmt_adv);
	} else
		mac_mode |= MAC_MODE_PORT_MODE_GMII;

	if (mac_mode != tp->mac_mode) {
		tp->mac_mode = mac_mode;
		tw32_f(MAC_MODE, tp->mac_mode);
		udelay(40);
	}

	if (tg3_asic_rev(tp) == ASIC_REV_5785) {
		if (phydev->speed == SPEED_10)
			tw32(MAC_MI_STAT,
			     MAC_MI_STAT_10MBPS_MODE |
			     MAC_MI_STAT_LNKSTAT_ATTN_ENAB);
		else
			tw32(MAC_MI_STAT, MAC_MI_STAT_LNKSTAT_ATTN_ENAB);
	}

	if (phydev->speed == SPEED_1000 && phydev->duplex == DUPLEX_HALF)
		tw32(MAC_TX_LENGTHS,
		     ((2 << TX_LENGTHS_IPG_CRS_SHIFT) |
		      (6 << TX_LENGTHS_IPG_SHIFT) |
		      (0xff << TX_LENGTHS_SLOT_TIME_SHIFT)));
	else
		tw32(MAC_TX_LENGTHS,
		     ((2 << TX_LENGTHS_IPG_CRS_SHIFT) |
		      (6 << TX_LENGTHS_IPG_SHIFT) |
		      (32 << TX_LENGTHS_SLOT_TIME_SHIFT)));

	if (phydev->link != tp->old_link ||
	    phydev->speed != tp->link_config.active_speed ||
	    phydev->duplex != tp->link_config.active_duplex ||
	    oldflowctrl != tp->link_config.active_flowctrl)
		linkmesg = 1;

	tp->old_link = phydev->link;
	tp->link_config.active_speed = phydev->speed;
	tp->link_config.active_duplex = phydev->duplex;

	spin_unlock_bh(&tp->lock);

	if (linkmesg)
		tg3_link_report(tp);
}