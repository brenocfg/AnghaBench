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
struct niu_link_config {scalar_t__ loopback_mode; scalar_t__ active_speed; scalar_t__ active_duplex; int advertising; scalar_t__ duplex; scalar_t__ speed; scalar_t__ autoneg; } ;
struct niu {int /*<<< orphan*/  port; int /*<<< orphan*/  phy_addr; struct niu_link_config link_config; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_1000HALF ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int ADVERTISE_CSMA ; 
 int ADVERTISE_PAUSE_CAP ; 
 int /*<<< orphan*/  BCM5464R_AUX_CTL ; 
 int BCM5464R_AUX_CTL_EXT_LB ; 
 int BCM5464R_AUX_CTL_WRITE_1 ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_FULLDPLX ; 
 int BMCR_LOOPBACK ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 int BMSR_100FULL ; 
 int BMSR_100HALF ; 
 int BMSR_10FULL ; 
 int BMSR_10HALF ; 
 int BMSR_ESTATEN ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 int ESTATUS_1000_TFULL ; 
 int ESTATUS_1000_THALF ; 
 scalar_t__ LOOPBACK_MAC ; 
 scalar_t__ LOOPBACK_PHY ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_ESTATUS ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ likely (int) ; 
 int mii_read (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_reset (struct niu*) ; 
 int mii_write (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mii_init_common(struct niu *np)
{
	struct niu_link_config *lp = &np->link_config;
	u16 bmcr, bmsr, adv, estat;
	int err;

	err = mii_reset(np);
	if (err)
		return err;

	err = mii_read(np, np->phy_addr, MII_BMSR);
	if (err < 0)
		return err;
	bmsr = err;

	estat = 0;
	if (bmsr & BMSR_ESTATEN) {
		err = mii_read(np, np->phy_addr, MII_ESTATUS);
		if (err < 0)
			return err;
		estat = err;
	}

	bmcr = 0;
	err = mii_write(np, np->phy_addr, MII_BMCR, bmcr);
	if (err)
		return err;

	if (lp->loopback_mode == LOOPBACK_MAC) {
		bmcr |= BMCR_LOOPBACK;
		if (lp->active_speed == SPEED_1000)
			bmcr |= BMCR_SPEED1000;
		if (lp->active_duplex == DUPLEX_FULL)
			bmcr |= BMCR_FULLDPLX;
	}

	if (lp->loopback_mode == LOOPBACK_PHY) {
		u16 aux;

		aux = (BCM5464R_AUX_CTL_EXT_LB |
		       BCM5464R_AUX_CTL_WRITE_1);
		err = mii_write(np, np->phy_addr, BCM5464R_AUX_CTL, aux);
		if (err)
			return err;
	}

	if (lp->autoneg) {
		u16 ctrl1000;

		adv = ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP;
		if ((bmsr & BMSR_10HALF) &&
			(lp->advertising & ADVERTISED_10baseT_Half))
			adv |= ADVERTISE_10HALF;
		if ((bmsr & BMSR_10FULL) &&
			(lp->advertising & ADVERTISED_10baseT_Full))
			adv |= ADVERTISE_10FULL;
		if ((bmsr & BMSR_100HALF) &&
			(lp->advertising & ADVERTISED_100baseT_Half))
			adv |= ADVERTISE_100HALF;
		if ((bmsr & BMSR_100FULL) &&
			(lp->advertising & ADVERTISED_100baseT_Full))
			adv |= ADVERTISE_100FULL;
		err = mii_write(np, np->phy_addr, MII_ADVERTISE, adv);
		if (err)
			return err;

		if (likely(bmsr & BMSR_ESTATEN)) {
			ctrl1000 = 0;
			if ((estat & ESTATUS_1000_THALF) &&
				(lp->advertising & ADVERTISED_1000baseT_Half))
				ctrl1000 |= ADVERTISE_1000HALF;
			if ((estat & ESTATUS_1000_TFULL) &&
				(lp->advertising & ADVERTISED_1000baseT_Full))
				ctrl1000 |= ADVERTISE_1000FULL;
			err = mii_write(np, np->phy_addr,
					MII_CTRL1000, ctrl1000);
			if (err)
				return err;
		}

		bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
	} else {
		/* !lp->autoneg */
		int fulldpx;

		if (lp->duplex == DUPLEX_FULL) {
			bmcr |= BMCR_FULLDPLX;
			fulldpx = 1;
		} else if (lp->duplex == DUPLEX_HALF)
			fulldpx = 0;
		else
			return -EINVAL;

		if (lp->speed == SPEED_1000) {
			/* if X-full requested while not supported, or
			   X-half requested while not supported... */
			if ((fulldpx && !(estat & ESTATUS_1000_TFULL)) ||
				(!fulldpx && !(estat & ESTATUS_1000_THALF)))
				return -EINVAL;
			bmcr |= BMCR_SPEED1000;
		} else if (lp->speed == SPEED_100) {
			if ((fulldpx && !(bmsr & BMSR_100FULL)) ||
				(!fulldpx && !(bmsr & BMSR_100HALF)))
				return -EINVAL;
			bmcr |= BMCR_SPEED100;
		} else if (lp->speed == SPEED_10) {
			if ((fulldpx && !(bmsr & BMSR_10FULL)) ||
				(!fulldpx && !(bmsr & BMSR_10HALF)))
				return -EINVAL;
		} else
			return -EINVAL;
	}

	err = mii_write(np, np->phy_addr, MII_BMCR, bmcr);
	if (err)
		return err;

#if 0
	err = mii_read(np, np->phy_addr, MII_BMCR);
	if (err < 0)
		return err;
	bmcr = err;

	err = mii_read(np, np->phy_addr, MII_BMSR);
	if (err < 0)
		return err;
	bmsr = err;

	pr_info("Port %u after MII init bmcr[%04x] bmsr[%04x]\n",
		np->port, bmcr, bmsr);
#endif

	return 0;
}