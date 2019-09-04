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
struct mii_phy {int speed; int duplex; scalar_t__ asym_pause; scalar_t__ pause; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_RESET ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 int DUPLEX_FULL ; 
 int EINVAL ; 
 int /*<<< orphan*/  MII_BMCR ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int phy_read (struct mii_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct mii_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int genmii_setup_forced(struct mii_phy *phy, int speed, int fd)
{
	int ctl;

	phy->autoneg = AUTONEG_DISABLE;
	phy->speed = speed;
	phy->duplex = fd;
	phy->pause = phy->asym_pause = 0;

	ctl = phy_read(phy, MII_BMCR);
	if (ctl < 0)
		return ctl;
	ctl &= ~(BMCR_FULLDPLX | BMCR_SPEED100 | BMCR_SPEED1000 | BMCR_ANENABLE);

	/* First clear the PHY */
	phy_write(phy, MII_BMCR, ctl | BMCR_RESET);

	/* Select speed & duplex */
	switch (speed) {
	case SPEED_10:
		break;
	case SPEED_100:
		ctl |= BMCR_SPEED100;
		break;
	case SPEED_1000:
		ctl |= BMCR_SPEED1000;
		break;
	default:
		return -EINVAL;
	}
	if (fd == DUPLEX_FULL)
		ctl |= BMCR_FULLDPLX;
	phy_write(phy, MII_BMCR, ctl);

	return 0;
}