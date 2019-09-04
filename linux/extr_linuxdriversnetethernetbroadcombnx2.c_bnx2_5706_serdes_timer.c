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
struct bnx2 {scalar_t__ link_up; int autoneg; int mii_bmcr; int phy_flags; int /*<<< orphan*/  phy_lock; void* current_interval; scalar_t__ serdes_an_pending; } ;

/* Variables and functions */
 int AUTONEG_SPEED ; 
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED1000 ; 
 int BNX2_PHY_FLAG_FORCED_DOWN ; 
 int BNX2_PHY_FLAG_PARALLEL_DETECT ; 
 void* BNX2_TIMER_INTERVAL ; 
 int MII_BNX2_MISC_SHADOW ; 
 int MISC_SHDW_AN_DBG ; 
 int MISC_SHDW_AN_DBG_NOSYNC ; 
 scalar_t__ bnx2_5706_serdes_has_link (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_5706s_force_link_dn (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_read_phy (struct bnx2*,int,int*) ; 
 int /*<<< orphan*/  bnx2_set_link (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_write_phy (struct bnx2*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnx2_5706_serdes_timer(struct bnx2 *bp)
{
	int check_link = 1;

	spin_lock(&bp->phy_lock);
	if (bp->serdes_an_pending) {
		bp->serdes_an_pending--;
		check_link = 0;
	} else if ((bp->link_up == 0) && (bp->autoneg & AUTONEG_SPEED)) {
		u32 bmcr;

		bp->current_interval = BNX2_TIMER_INTERVAL;

		bnx2_read_phy(bp, bp->mii_bmcr, &bmcr);

		if (bmcr & BMCR_ANENABLE) {
			if (bnx2_5706_serdes_has_link(bp)) {
				bmcr &= ~BMCR_ANENABLE;
				bmcr |= BMCR_SPEED1000 | BMCR_FULLDPLX;
				bnx2_write_phy(bp, bp->mii_bmcr, bmcr);
				bp->phy_flags |= BNX2_PHY_FLAG_PARALLEL_DETECT;
			}
		}
	}
	else if ((bp->link_up) && (bp->autoneg & AUTONEG_SPEED) &&
		 (bp->phy_flags & BNX2_PHY_FLAG_PARALLEL_DETECT)) {
		u32 phy2;

		bnx2_write_phy(bp, 0x17, 0x0f01);
		bnx2_read_phy(bp, 0x15, &phy2);
		if (phy2 & 0x20) {
			u32 bmcr;

			bnx2_read_phy(bp, bp->mii_bmcr, &bmcr);
			bmcr |= BMCR_ANENABLE;
			bnx2_write_phy(bp, bp->mii_bmcr, bmcr);

			bp->phy_flags &= ~BNX2_PHY_FLAG_PARALLEL_DETECT;
		}
	} else
		bp->current_interval = BNX2_TIMER_INTERVAL;

	if (check_link) {
		u32 val;

		bnx2_write_phy(bp, MII_BNX2_MISC_SHADOW, MISC_SHDW_AN_DBG);
		bnx2_read_phy(bp, MII_BNX2_MISC_SHADOW, &val);
		bnx2_read_phy(bp, MII_BNX2_MISC_SHADOW, &val);

		if (bp->link_up && (val & MISC_SHDW_AN_DBG_NOSYNC)) {
			if (!(bp->phy_flags & BNX2_PHY_FLAG_FORCED_DOWN)) {
				bnx2_5706s_force_link_dn(bp, 1);
				bp->phy_flags |= BNX2_PHY_FLAG_FORCED_DOWN;
			} else
				bnx2_set_link(bp);
		} else if (!bp->link_up && !(val & MISC_SHDW_AN_DBG_NOSYNC))
			bnx2_set_link(bp);
	}
	spin_unlock(&bp->phy_lock);
}