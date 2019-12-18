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
struct mii_phy {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int BCM5461_FIBER_DUPLEX ; 
 int BCM5461_MODE_MASK ; 
 int BCM54XX_COPPER ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  MII_NCONFIG ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int bcm54xx_read_link (struct mii_phy*) ; 
 int sungem_phy_read (struct mii_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sungem_phy_write (struct mii_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm5461_read_link(struct mii_phy* phy)
{
	u32 phy_reg;
	int mode;

	/* find out in what mode we are */
	sungem_phy_write(phy, MII_NCONFIG, 0x7c00);
	phy_reg = sungem_phy_read(phy, MII_NCONFIG);

	mode = (phy_reg & BCM5461_MODE_MASK ) >> 1;

	if ( mode == BCM54XX_COPPER) {
		return bcm54xx_read_link(phy);
	}

	phy->speed = SPEED_1000;

	/* find out whether we are running half- or full duplex */
	sungem_phy_write(phy, MII_NCONFIG, 0x7000);
	phy_reg = sungem_phy_read(phy, MII_NCONFIG);

	if (phy_reg & BCM5461_FIBER_DUPLEX)
		phy->duplex |=  DUPLEX_FULL;
	else
		phy->duplex |=  DUPLEX_HALF;

	return 0;
}