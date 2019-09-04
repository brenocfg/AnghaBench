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
struct bnx2 {int /*<<< orphan*/  phy_flags; scalar_t__ link_up; void* duplex; void* line_speed; int /*<<< orphan*/  mii_lpa; int /*<<< orphan*/  mii_adv; int /*<<< orphan*/  mii_bmcr; } ;

/* Variables and functions */
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_1000HALF ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int /*<<< orphan*/  BNX2_PHY_FLAG_MDIX ; 
 void* DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 int EXT_STATUS_MDIX ; 
 int /*<<< orphan*/  MII_BNX2_EXT_STATUS ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_STAT1000 ; 
 void* SPEED_10 ; 
 void* SPEED_100 ; 
 void* SPEED_1000 ; 
 int /*<<< orphan*/  bnx2_read_phy (struct bnx2*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
bnx2_copper_linkup(struct bnx2 *bp)
{
	u32 bmcr;

	bp->phy_flags &= ~BNX2_PHY_FLAG_MDIX;

	bnx2_read_phy(bp, bp->mii_bmcr, &bmcr);
	if (bmcr & BMCR_ANENABLE) {
		u32 local_adv, remote_adv, common;

		bnx2_read_phy(bp, MII_CTRL1000, &local_adv);
		bnx2_read_phy(bp, MII_STAT1000, &remote_adv);

		common = local_adv & (remote_adv >> 2);
		if (common & ADVERTISE_1000FULL) {
			bp->line_speed = SPEED_1000;
			bp->duplex = DUPLEX_FULL;
		}
		else if (common & ADVERTISE_1000HALF) {
			bp->line_speed = SPEED_1000;
			bp->duplex = DUPLEX_HALF;
		}
		else {
			bnx2_read_phy(bp, bp->mii_adv, &local_adv);
			bnx2_read_phy(bp, bp->mii_lpa, &remote_adv);

			common = local_adv & remote_adv;
			if (common & ADVERTISE_100FULL) {
				bp->line_speed = SPEED_100;
				bp->duplex = DUPLEX_FULL;
			}
			else if (common & ADVERTISE_100HALF) {
				bp->line_speed = SPEED_100;
				bp->duplex = DUPLEX_HALF;
			}
			else if (common & ADVERTISE_10FULL) {
				bp->line_speed = SPEED_10;
				bp->duplex = DUPLEX_FULL;
			}
			else if (common & ADVERTISE_10HALF) {
				bp->line_speed = SPEED_10;
				bp->duplex = DUPLEX_HALF;
			}
			else {
				bp->line_speed = 0;
				bp->link_up = 0;
			}
		}
	}
	else {
		if (bmcr & BMCR_SPEED100) {
			bp->line_speed = SPEED_100;
		}
		else {
			bp->line_speed = SPEED_10;
		}
		if (bmcr & BMCR_FULLDPLX) {
			bp->duplex = DUPLEX_FULL;
		}
		else {
			bp->duplex = DUPLEX_HALF;
		}
	}

	if (bp->link_up) {
		u32 ext_status;

		bnx2_read_phy(bp, MII_BNX2_EXT_STATUS, &ext_status);
		if (ext_status & EXT_STATUS_MDIX)
			bp->phy_flags |= BNX2_PHY_FLAG_MDIX;
	}

	return 0;
}