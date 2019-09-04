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
struct mii_phy {scalar_t__ mode; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_ISOLATE ; 
 int BMCR_RESET ; 
 int MII_BMCR ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int gpcs_phy_read (struct mii_phy*,int) ; 
 int /*<<< orphan*/  gpcs_phy_write (struct mii_phy*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int emac_mii_reset_gpcs(struct mii_phy *phy)
{
	int val;
	int limit = 10000;

	val = gpcs_phy_read(phy, MII_BMCR);
	val &= ~(BMCR_ISOLATE | BMCR_ANENABLE);
	val |= BMCR_RESET;
	gpcs_phy_write(phy, MII_BMCR, val);

	udelay(300);

	while (--limit) {
		val = gpcs_phy_read(phy, MII_BMCR);
		if (val >= 0 && (val & BMCR_RESET) == 0)
			break;
		udelay(10);
	}
	if ((val & BMCR_ISOLATE) && limit > 0)
		gpcs_phy_write(phy, MII_BMCR, val & ~BMCR_ISOLATE);

	if (limit > 0 && phy->mode == PHY_INTERFACE_MODE_SGMII) {
		/* Configure GPCS interface to recommended setting for SGMII */
		gpcs_phy_write(phy, 0x04, 0x8120); /* AsymPause, FDX */
		gpcs_phy_write(phy, 0x07, 0x2801); /* msg_pg, toggle */
		gpcs_phy_write(phy, 0x00, 0x0140); /* 1Gbps, FDX     */
	}

	return limit <= 0;
}