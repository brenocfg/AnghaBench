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
struct cas {int lstate; int link_fcntl; int timer_ticks; int cas_flags; void* link_transition; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int CAS_BMCR_SPEED1000 ; 
 int CAS_FLAG_1000MB_CAP ; 
 void* LINK_TRANSITION_LINK_CONFIG ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int cas_phy_read (struct cas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_phy_write (struct cas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  link ; 
#define  link_aneg 130 
 int link_force_ok ; 
#define  link_force_ret 129 
#define  link_force_try 128 
 int /*<<< orphan*/  netif_info (struct cas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline int cas_mdio_link_not_up(struct cas *cp)
{
	u16 val;

	switch (cp->lstate) {
	case link_force_ret:
		netif_info(cp, link, cp->dev, "Autoneg failed again, keeping forced mode\n");
		cas_phy_write(cp, MII_BMCR, cp->link_fcntl);
		cp->timer_ticks = 5;
		cp->lstate = link_force_ok;
		cp->link_transition = LINK_TRANSITION_LINK_CONFIG;
		break;

	case link_aneg:
		val = cas_phy_read(cp, MII_BMCR);

		/* Try forced modes. we try things in the following order:
		 * 1000 full -> 100 full/half -> 10 half
		 */
		val &= ~(BMCR_ANRESTART | BMCR_ANENABLE);
		val |= BMCR_FULLDPLX;
		val |= (cp->cas_flags & CAS_FLAG_1000MB_CAP) ?
			CAS_BMCR_SPEED1000 : BMCR_SPEED100;
		cas_phy_write(cp, MII_BMCR, val);
		cp->timer_ticks = 5;
		cp->lstate = link_force_try;
		cp->link_transition = LINK_TRANSITION_LINK_CONFIG;
		break;

	case link_force_try:
		/* Downgrade from 1000 to 100 to 10 Mbps if necessary. */
		val = cas_phy_read(cp, MII_BMCR);
		cp->timer_ticks = 5;
		if (val & CAS_BMCR_SPEED1000) { /* gigabit */
			val &= ~CAS_BMCR_SPEED1000;
			val |= (BMCR_SPEED100 | BMCR_FULLDPLX);
			cas_phy_write(cp, MII_BMCR, val);
			break;
		}

		if (val & BMCR_SPEED100) {
			if (val & BMCR_FULLDPLX) /* fd failed */
				val &= ~BMCR_FULLDPLX;
			else { /* 100Mbps failed */
				val &= ~BMCR_SPEED100;
			}
			cas_phy_write(cp, MII_BMCR, val);
			break;
		}
	default:
		break;
	}
	return 0;
}