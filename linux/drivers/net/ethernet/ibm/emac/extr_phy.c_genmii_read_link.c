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
struct mii_phy {scalar_t__ autoneg; int features; scalar_t__ duplex; int pause; int asym_pause; void* speed; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 scalar_t__ DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 int LPA_1000FULL ; 
 int LPA_1000HALF ; 
 int LPA_100FULL ; 
 int LPA_100HALF ; 
 int LPA_10FULL ; 
 int LPA_PAUSE_ASYM ; 
 int LPA_PAUSE_CAP ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  MII_STAT1000 ; 
 void* SPEED_10 ; 
 void* SPEED_100 ; 
 void* SPEED_1000 ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int phy_read (struct mii_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int genmii_read_link(struct mii_phy *phy)
{
	if (phy->autoneg == AUTONEG_ENABLE) {
		int glpa = 0;
		int lpa = phy_read(phy, MII_LPA) & phy_read(phy, MII_ADVERTISE);
		if (lpa < 0)
			return lpa;

		if (phy->features &
		    (SUPPORTED_1000baseT_Full | SUPPORTED_1000baseT_Half)) {
			int adv = phy_read(phy, MII_CTRL1000);
			glpa = phy_read(phy, MII_STAT1000);

			if (glpa < 0 || adv < 0)
				return adv;

			glpa &= adv << 2;
		}

		phy->speed = SPEED_10;
		phy->duplex = DUPLEX_HALF;
		phy->pause = phy->asym_pause = 0;

		if (glpa & (LPA_1000FULL | LPA_1000HALF)) {
			phy->speed = SPEED_1000;
			if (glpa & LPA_1000FULL)
				phy->duplex = DUPLEX_FULL;
		} else if (lpa & (LPA_100FULL | LPA_100HALF)) {
			phy->speed = SPEED_100;
			if (lpa & LPA_100FULL)
				phy->duplex = DUPLEX_FULL;
		} else if (lpa & LPA_10FULL)
			phy->duplex = DUPLEX_FULL;

		if (phy->duplex == DUPLEX_FULL) {
			phy->pause = lpa & LPA_PAUSE_CAP ? 1 : 0;
			phy->asym_pause = lpa & LPA_PAUSE_ASYM ? 1 : 0;
		}
	} else {
		int bmcr = phy_read(phy, MII_BMCR);
		if (bmcr < 0)
			return bmcr;

		if (bmcr & BMCR_FULLDPLX)
			phy->duplex = DUPLEX_FULL;
		else
			phy->duplex = DUPLEX_HALF;
		if (bmcr & BMCR_SPEED1000)
			phy->speed = SPEED_1000;
		else if (bmcr & BMCR_SPEED100)
			phy->speed = SPEED_100;
		else
			phy->speed = SPEED_10;

		phy->pause = phy->asym_pause = 0;
	}
	return 0;
}