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
typedef  int /*<<< orphan*/  u32 ;
struct temac_local {int last_link; int /*<<< orphan*/  indirect_lock; } ;
struct phy_device {int speed; int duplex; int link; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  XTE_EMCFG_LINKSPD_10 ; 
 int /*<<< orphan*/  XTE_EMCFG_LINKSPD_100 ; 
 int /*<<< orphan*/  XTE_EMCFG_LINKSPD_1000 ; 
 int /*<<< orphan*/  XTE_EMCFG_LINKSPD_MASK ; 
 int /*<<< orphan*/  XTE_EMCFG_OFFSET ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  temac_indirect_in32_locked (struct temac_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temac_indirect_out32_locked (struct temac_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void temac_adjust_link(struct net_device *ndev)
{
	struct temac_local *lp = netdev_priv(ndev);
	struct phy_device *phy = ndev->phydev;
	u32 mii_speed;
	int link_state;
	unsigned long flags;

	/* hash together the state values to decide if something has changed */
	link_state = phy->speed | (phy->duplex << 1) | phy->link;

	if (lp->last_link != link_state) {
		spin_lock_irqsave(lp->indirect_lock, flags);
		mii_speed = temac_indirect_in32_locked(lp, XTE_EMCFG_OFFSET);
		mii_speed &= ~XTE_EMCFG_LINKSPD_MASK;

		switch (phy->speed) {
		case SPEED_1000: mii_speed |= XTE_EMCFG_LINKSPD_1000; break;
		case SPEED_100: mii_speed |= XTE_EMCFG_LINKSPD_100; break;
		case SPEED_10: mii_speed |= XTE_EMCFG_LINKSPD_10; break;
		}

		/* Write new speed setting out to TEMAC */
		temac_indirect_out32_locked(lp, XTE_EMCFG_OFFSET, mii_speed);
		spin_unlock_irqrestore(lp->indirect_lock, flags);

		lp->last_link = link_state;
		phy_print_status(phy);
	}
}