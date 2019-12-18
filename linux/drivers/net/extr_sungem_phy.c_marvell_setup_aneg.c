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
typedef  int u32 ;
typedef  int u16 ;
struct mii_phy {int autoneg; int advertising; scalar_t__ pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int ADVERTISE_100BASE4 ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int ADVERTISE_ALL ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  MII_1000BASETCONTROL ; 
 int MII_1000BASETCONTROL_FULLDUPLEXCAP ; 
 int MII_1000BASETCONTROL_HALFDUPLEXCAP ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_M1011_PHY_SPEC_CONTROL ; 
 int MII_M1011_PHY_SPEC_CONTROL_AUTO_MDIX ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int sungem_phy_read (struct mii_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sungem_phy_write (struct mii_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int marvell_setup_aneg(struct mii_phy *phy, u32 advertise)
{
	u16 ctl, adv;

	phy->autoneg = 1;
	phy->speed = SPEED_10;
	phy->duplex = DUPLEX_HALF;
	phy->pause = 0;
	phy->advertising = advertise;

	/* Setup standard advertise */
	adv = sungem_phy_read(phy, MII_ADVERTISE);
	adv &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4);
	if (advertise & ADVERTISED_10baseT_Half)
		adv |= ADVERTISE_10HALF;
	if (advertise & ADVERTISED_10baseT_Full)
		adv |= ADVERTISE_10FULL;
	if (advertise & ADVERTISED_100baseT_Half)
		adv |= ADVERTISE_100HALF;
	if (advertise & ADVERTISED_100baseT_Full)
		adv |= ADVERTISE_100FULL;
	if (advertise & ADVERTISED_Pause)
		adv |= ADVERTISE_PAUSE_CAP;
	if (advertise & ADVERTISED_Asym_Pause)
		adv |= ADVERTISE_PAUSE_ASYM;
	sungem_phy_write(phy, MII_ADVERTISE, adv);

	/* Setup 1000BT advertise & enable crossover detect
	 * XXX How do we advertise 1000BT ? Darwin source is
	 * confusing here, they read from specific control and
	 * write to control... Someone has specs for those
	 * beasts ?
	 */
	adv = sungem_phy_read(phy, MII_M1011_PHY_SPEC_CONTROL);
	adv |= MII_M1011_PHY_SPEC_CONTROL_AUTO_MDIX;
	adv &= ~(MII_1000BASETCONTROL_FULLDUPLEXCAP |
			MII_1000BASETCONTROL_HALFDUPLEXCAP);
	if (advertise & SUPPORTED_1000baseT_Half)
		adv |= MII_1000BASETCONTROL_HALFDUPLEXCAP;
	if (advertise & SUPPORTED_1000baseT_Full)
		adv |= MII_1000BASETCONTROL_FULLDUPLEXCAP;
	sungem_phy_write(phy, MII_1000BASETCONTROL, adv);

	/* Start/Restart aneg */
	ctl = sungem_phy_read(phy, MII_BMCR);
	ctl |= (BMCR_ANENABLE | BMCR_ANRESTART);
	sungem_phy_write(phy, MII_BMCR, ctl);

	return 0;
}