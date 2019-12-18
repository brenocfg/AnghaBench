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
struct adapter {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int phy_query_bb_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_bb_reg (struct adapter*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rOFDM0_ECCAThreshold ; 
 int /*<<< orphan*/  rOFDM0_RxIQExtAnta ; 
 int /*<<< orphan*/  rOFDM0_XARxIQImbalance ; 
 int /*<<< orphan*/  rOFDM0_XATxIQImbalance ; 
 int /*<<< orphan*/  rOFDM0_XCTxAFE ; 

__attribute__((used)) static void patha_fill_iqk(struct adapter *adapt, bool iqkok, s32 result[][8],
			   u8 final_candidate, bool txonly)
{
	u32 oldval_0, x, tx0_a, reg;
	s32 y, tx0_c;

	if (final_candidate == 0xFF) {
		return;
	} else if (iqkok) {
		oldval_0 = (phy_query_bb_reg(adapt, rOFDM0_XATxIQImbalance, bMaskDWord) >> 22) & 0x3FF;

		x = result[final_candidate][0];
		if ((x & 0x00000200) != 0)
			x = x | 0xFFFFFC00;

		tx0_a = (x * oldval_0) >> 8;
		phy_set_bb_reg(adapt, rOFDM0_XATxIQImbalance, 0x3FF, tx0_a);
		phy_set_bb_reg(adapt, rOFDM0_ECCAThreshold, BIT(31),
			       ((x * oldval_0>>7) & 0x1));

		y = result[final_candidate][1];
		if ((y & 0x00000200) != 0)
			y = y | 0xFFFFFC00;

		tx0_c = (y * oldval_0) >> 8;
		phy_set_bb_reg(adapt, rOFDM0_XCTxAFE, 0xF0000000,
			       ((tx0_c&0x3C0)>>6));
		phy_set_bb_reg(adapt, rOFDM0_XATxIQImbalance, 0x003F0000,
			       (tx0_c&0x3F));
		phy_set_bb_reg(adapt, rOFDM0_ECCAThreshold, BIT(29),
			       ((y * oldval_0>>7) & 0x1));

		if (txonly)
			return;

		reg = result[final_candidate][2];
		phy_set_bb_reg(adapt, rOFDM0_XARxIQImbalance, 0x3FF, reg);

		reg = result[final_candidate][3] & 0x3F;
		phy_set_bb_reg(adapt, rOFDM0_XARxIQImbalance, 0xFC00, reg);

		reg = (result[final_candidate][3] >> 6) & 0xF;
		phy_set_bb_reg(adapt, rOFDM0_RxIQExtAnta, 0xF0000000, reg);
	}
}