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
struct bnx2 {int phy_flags; int /*<<< orphan*/  mii_up1; } ;

/* Variables and functions */
 int BCM5708S_UP1_2G5 ; 
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int BNX2_PHY_FLAG_2_5G_CAPABLE ; 
 int /*<<< orphan*/  MII_BNX2_BLK_ADDR ; 
 int MII_BNX2_BLK_ADDR_COMBO_IEEEB0 ; 
 int MII_BNX2_BLK_ADDR_OVER1G ; 
 int /*<<< orphan*/  bnx2_read_phy (struct bnx2*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2_write_phy (struct bnx2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bnx2_test_and_disable_2g5(struct bnx2 *bp)
{
	u32 up1;
	int ret = 0;

	if (!(bp->phy_flags & BNX2_PHY_FLAG_2_5G_CAPABLE))
		return 0;

	if (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		bnx2_write_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_OVER1G);

	bnx2_read_phy(bp, bp->mii_up1, &up1);
	if (up1 & BCM5708S_UP1_2G5) {
		up1 &= ~BCM5708S_UP1_2G5;
		bnx2_write_phy(bp, bp->mii_up1, up1);
		ret = 1;
	}

	if (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		bnx2_write_phy(bp, MII_BNX2_BLK_ADDR,
			       MII_BNX2_BLK_ADDR_COMBO_IEEEB0);

	return ret;
}