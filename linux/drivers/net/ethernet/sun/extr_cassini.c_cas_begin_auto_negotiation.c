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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ autoneg; scalar_t__ speed; scalar_t__ duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct cas {int lstate; int link_cntl; int phy_type; int /*<<< orphan*/  link_timer; scalar_t__ timer_ticks; void* link_transition; scalar_t__ regs; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  reset_task_pending_all; int /*<<< orphan*/  reset_task_pending; int /*<<< orphan*/  dev; int /*<<< orphan*/  hw_running; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int CAS_BMCR_SPEED1000 ; 
 scalar_t__ CAS_LINK_TIMEOUT ; 
 int CAS_PHY_SERDES ; 
 scalar_t__ DUPLEX_FULL ; 
 void* LINK_TRANSITION_LINK_CONFIG ; 
 void* LINK_TRANSITION_LINK_DOWN ; 
 int /*<<< orphan*/  MII_BMCR ; 
 scalar_t__ PCS_MII_AUTONEG_EN ; 
 scalar_t__ PCS_MII_CTRL_DUPLEX ; 
 scalar_t__ PCS_MII_RESTART_AUTONEG ; 
 scalar_t__ REG_PCS_MII_CTRL ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cas_mif_poll (struct cas*,int) ; 
 int cas_phy_read (struct cas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_phy_write (struct cas*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 void* link_aneg ; 
 int link_down ; 
 void* link_force_ok ; 
 int link_up ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void cas_begin_auto_negotiation(struct cas *cp,
				       const struct ethtool_link_ksettings *ep)
{
	u16 ctl;
#if 1
	int lcntl;
	int changed = 0;
	int oldstate = cp->lstate;
	int link_was_not_down = !(oldstate == link_down);
#endif
	/* Setup link parameters */
	if (!ep)
		goto start_aneg;
	lcntl = cp->link_cntl;
	if (ep->base.autoneg == AUTONEG_ENABLE) {
		cp->link_cntl = BMCR_ANENABLE;
	} else {
		u32 speed = ep->base.speed;
		cp->link_cntl = 0;
		if (speed == SPEED_100)
			cp->link_cntl |= BMCR_SPEED100;
		else if (speed == SPEED_1000)
			cp->link_cntl |= CAS_BMCR_SPEED1000;
		if (ep->base.duplex == DUPLEX_FULL)
			cp->link_cntl |= BMCR_FULLDPLX;
	}
#if 1
	changed = (lcntl != cp->link_cntl);
#endif
start_aneg:
	if (cp->lstate == link_up) {
		netdev_info(cp->dev, "PCS link down\n");
	} else {
		if (changed) {
			netdev_info(cp->dev, "link configuration changed\n");
		}
	}
	cp->lstate = link_down;
	cp->link_transition = LINK_TRANSITION_LINK_DOWN;
	if (!cp->hw_running)
		return;
#if 1
	/*
	 * WTZ: If the old state was link_up, we turn off the carrier
	 * to replicate everything we do elsewhere on a link-down
	 * event when we were already in a link-up state..
	 */
	if (oldstate == link_up)
		netif_carrier_off(cp->dev);
	if (changed  && link_was_not_down) {
		/*
		 * WTZ: This branch will simply schedule a full reset after
		 * we explicitly changed link modes in an ioctl. See if this
		 * fixes the link-problems we were having for forced mode.
		 */
		atomic_inc(&cp->reset_task_pending);
		atomic_inc(&cp->reset_task_pending_all);
		schedule_work(&cp->reset_task);
		cp->timer_ticks = 0;
		mod_timer(&cp->link_timer, jiffies + CAS_LINK_TIMEOUT);
		return;
	}
#endif
	if (cp->phy_type & CAS_PHY_SERDES) {
		u32 val = readl(cp->regs + REG_PCS_MII_CTRL);

		if (cp->link_cntl & BMCR_ANENABLE) {
			val |= (PCS_MII_RESTART_AUTONEG | PCS_MII_AUTONEG_EN);
			cp->lstate = link_aneg;
		} else {
			if (cp->link_cntl & BMCR_FULLDPLX)
				val |= PCS_MII_CTRL_DUPLEX;
			val &= ~PCS_MII_AUTONEG_EN;
			cp->lstate = link_force_ok;
		}
		cp->link_transition = LINK_TRANSITION_LINK_CONFIG;
		writel(val, cp->regs + REG_PCS_MII_CTRL);

	} else {
		cas_mif_poll(cp, 0);
		ctl = cas_phy_read(cp, MII_BMCR);
		ctl &= ~(BMCR_FULLDPLX | BMCR_SPEED100 |
			 CAS_BMCR_SPEED1000 | BMCR_ANENABLE);
		ctl |= cp->link_cntl;
		if (ctl & BMCR_ANENABLE) {
			ctl |= BMCR_ANRESTART;
			cp->lstate = link_aneg;
		} else {
			cp->lstate = link_force_ok;
		}
		cp->link_transition = LINK_TRANSITION_LINK_CONFIG;
		cas_phy_write(cp, MII_BMCR, ctl);
		cas_mif_poll(cp, 1);
	}

	cp->timer_ticks = 0;
	mod_timer(&cp->link_timer, jiffies + CAS_LINK_TIMEOUT);
}