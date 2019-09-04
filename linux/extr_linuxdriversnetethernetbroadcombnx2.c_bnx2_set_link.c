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
typedef  int u8 ;
typedef  int u32 ;
struct bnx2 {scalar_t__ loopback; int link_up; int phy_flags; int autoneg; int /*<<< orphan*/  mii_bmcr; int /*<<< orphan*/  mii_bmsr1; } ;

/* Variables and functions */
 int AUTONEG_SPEED ; 
 int BMCR_ANENABLE ; 
 int BMSR_LSTATUS ; 
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5706 ; 
 scalar_t__ BNX2_CHIP_5708 ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int /*<<< orphan*/  BNX2_EMAC_STATUS ; 
 int BNX2_EMAC_STATUS_LINK ; 
 int BNX2_PHY_FLAG_FORCED_DOWN ; 
 int BNX2_PHY_FLAG_PARALLEL_DETECT ; 
 int BNX2_PHY_FLAG_REMOTE_PHY_CAP ; 
 int BNX2_PHY_FLAG_SERDES ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 scalar_t__ MAC_LOOPBACK ; 
 int /*<<< orphan*/  MII_BNX2_MISC_SHADOW ; 
 int MISC_SHDW_AN_DBG ; 
 int MISC_SHDW_AN_DBG_NOSYNC ; 
 scalar_t__ PHY_LOOPBACK ; 
 int /*<<< orphan*/  bnx2_5706s_force_link_dn (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_5706s_linkup (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_5708s_linkup (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_5709s_linkup (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_copper_linkup (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_disable_bmsr1 (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_disable_forced_2g5 (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_enable_bmsr1 (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_read_phy (struct bnx2*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2_report_link (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_resolve_flow_ctrl (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_set_mac_link (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_write_phy (struct bnx2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bnx2_set_link(struct bnx2 *bp)
{
	u32 bmsr;
	u8 link_up;

	if (bp->loopback == MAC_LOOPBACK || bp->loopback == PHY_LOOPBACK) {
		bp->link_up = 1;
		return 0;
	}

	if (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP)
		return 0;

	link_up = bp->link_up;

	bnx2_enable_bmsr1(bp);
	bnx2_read_phy(bp, bp->mii_bmsr1, &bmsr);
	bnx2_read_phy(bp, bp->mii_bmsr1, &bmsr);
	bnx2_disable_bmsr1(bp);

	if ((bp->phy_flags & BNX2_PHY_FLAG_SERDES) &&
	    (BNX2_CHIP(bp) == BNX2_CHIP_5706)) {
		u32 val, an_dbg;

		if (bp->phy_flags & BNX2_PHY_FLAG_FORCED_DOWN) {
			bnx2_5706s_force_link_dn(bp, 0);
			bp->phy_flags &= ~BNX2_PHY_FLAG_FORCED_DOWN;
		}
		val = BNX2_RD(bp, BNX2_EMAC_STATUS);

		bnx2_write_phy(bp, MII_BNX2_MISC_SHADOW, MISC_SHDW_AN_DBG);
		bnx2_read_phy(bp, MII_BNX2_MISC_SHADOW, &an_dbg);
		bnx2_read_phy(bp, MII_BNX2_MISC_SHADOW, &an_dbg);

		if ((val & BNX2_EMAC_STATUS_LINK) &&
		    !(an_dbg & MISC_SHDW_AN_DBG_NOSYNC))
			bmsr |= BMSR_LSTATUS;
		else
			bmsr &= ~BMSR_LSTATUS;
	}

	if (bmsr & BMSR_LSTATUS) {
		bp->link_up = 1;

		if (bp->phy_flags & BNX2_PHY_FLAG_SERDES) {
			if (BNX2_CHIP(bp) == BNX2_CHIP_5706)
				bnx2_5706s_linkup(bp);
			else if (BNX2_CHIP(bp) == BNX2_CHIP_5708)
				bnx2_5708s_linkup(bp);
			else if (BNX2_CHIP(bp) == BNX2_CHIP_5709)
				bnx2_5709s_linkup(bp);
		}
		else {
			bnx2_copper_linkup(bp);
		}
		bnx2_resolve_flow_ctrl(bp);
	}
	else {
		if ((bp->phy_flags & BNX2_PHY_FLAG_SERDES) &&
		    (bp->autoneg & AUTONEG_SPEED))
			bnx2_disable_forced_2g5(bp);

		if (bp->phy_flags & BNX2_PHY_FLAG_PARALLEL_DETECT) {
			u32 bmcr;

			bnx2_read_phy(bp, bp->mii_bmcr, &bmcr);
			bmcr |= BMCR_ANENABLE;
			bnx2_write_phy(bp, bp->mii_bmcr, bmcr);

			bp->phy_flags &= ~BNX2_PHY_FLAG_PARALLEL_DETECT;
		}
		bp->link_up = 0;
	}

	if (bp->link_up != link_up) {
		bnx2_report_link(bp);
	}

	bnx2_set_mac_link(bp);

	return 0;
}