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
typedef  scalar_t__ u32 ;
struct bnx2 {scalar_t__ func; int /*<<< orphan*/  phy_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_MISC_DUAL_MEDIA_CTRL ; 
 scalar_t__ BNX2_MISC_DUAL_MEDIA_CTRL_BOND_ID ; 
 scalar_t__ BNX2_MISC_DUAL_MEDIA_CTRL_BOND_ID_C ; 
 scalar_t__ BNX2_MISC_DUAL_MEDIA_CTRL_BOND_ID_S ; 
 scalar_t__ BNX2_MISC_DUAL_MEDIA_CTRL_PHY_CTRL ; 
 scalar_t__ BNX2_MISC_DUAL_MEDIA_CTRL_PHY_CTRL_STRAP ; 
 scalar_t__ BNX2_MISC_DUAL_MEDIA_CTRL_STRAP_OVERRIDE ; 
 int /*<<< orphan*/  BNX2_PHY_FLAG_SERDES ; 
 scalar_t__ BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnx2_get_5709_media(struct bnx2 *bp)
{
	u32 val = BNX2_RD(bp, BNX2_MISC_DUAL_MEDIA_CTRL);
	u32 bond_id = val & BNX2_MISC_DUAL_MEDIA_CTRL_BOND_ID;
	u32 strap;

	if (bond_id == BNX2_MISC_DUAL_MEDIA_CTRL_BOND_ID_C)
		return;
	else if (bond_id == BNX2_MISC_DUAL_MEDIA_CTRL_BOND_ID_S) {
		bp->phy_flags |= BNX2_PHY_FLAG_SERDES;
		return;
	}

	if (val & BNX2_MISC_DUAL_MEDIA_CTRL_STRAP_OVERRIDE)
		strap = (val & BNX2_MISC_DUAL_MEDIA_CTRL_PHY_CTRL) >> 21;
	else
		strap = (val & BNX2_MISC_DUAL_MEDIA_CTRL_PHY_CTRL_STRAP) >> 8;

	if (bp->func == 0) {
		switch (strap) {
		case 0x4:
		case 0x5:
		case 0x6:
			bp->phy_flags |= BNX2_PHY_FLAG_SERDES;
			return;
		}
	} else {
		switch (strap) {
		case 0x1:
		case 0x2:
		case 0x4:
			bp->phy_flags |= BNX2_PHY_FLAG_SERDES;
			return;
		}
	}
}