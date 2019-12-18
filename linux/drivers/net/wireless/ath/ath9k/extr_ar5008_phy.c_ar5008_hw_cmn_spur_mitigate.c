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
struct ath_hw {int dummy; } ;
struct ath9k_channel {int dummy; } ;
typedef  int int8_t ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int const AR_PHY_BIN_MASK2_1 ; 
 int const AR_PHY_BIN_MASK2_2 ; 
 int const AR_PHY_BIN_MASK2_3 ; 
 int const AR_PHY_BIN_MASK2_4 ; 
 int const AR_PHY_BIN_MASK_1 ; 
 int const AR_PHY_BIN_MASK_2 ; 
 int const AR_PHY_BIN_MASK_3 ; 
#define  AR_PHY_CHANNEL_MASK_01_30 135 
#define  AR_PHY_CHANNEL_MASK_31_60 134 
 int const AR_PHY_MASK2_M_00_15 ; 
 int const AR_PHY_MASK2_M_16_30 ; 
 int const AR_PHY_MASK2_M_31_45 ; 
 int const AR_PHY_MASK2_P_15_01 ; 
 int const AR_PHY_MASK2_P_30_16 ; 
 int const AR_PHY_MASK2_P_45_31 ; 
 int const AR_PHY_MASK2_P_61_45 ; 
 int const AR_PHY_MASK_CTL ; 
#define  AR_PHY_PILOT_MASK_01_30 133 
#define  AR_PHY_PILOT_MASK_31_60 132 
#define  AR_PHY_TIMING10 131 
#define  AR_PHY_TIMING7 130 
#define  AR_PHY_TIMING8 129 
#define  AR_PHY_TIMING9 128 
 int const AR_PHY_VIT_MASK2_M_46_61 ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int const,int) ; 
 size_t abs (int) ; 

void ar5008_hw_cmn_spur_mitigate(struct ath_hw *ah,
			  struct ath9k_channel *chan, int bin)
{
	int cur_bin;
	int upper, lower, cur_vit_mask;
	int i;
	int8_t mask_m[123] = {0};
	int8_t mask_p[123] = {0};
	int8_t mask_amt;
	int tmp_mask;
	static const int pilot_mask_reg[4] = {
		AR_PHY_TIMING7, AR_PHY_TIMING8,
		AR_PHY_PILOT_MASK_01_30, AR_PHY_PILOT_MASK_31_60
	};
	static const int chan_mask_reg[4] = {
		AR_PHY_TIMING9, AR_PHY_TIMING10,
		AR_PHY_CHANNEL_MASK_01_30, AR_PHY_CHANNEL_MASK_31_60
	};
	static const int inc[4] = { 0, 100, 0, 0 };

	cur_bin = -6000;
	upper = bin + 100;
	lower = bin - 100;

	for (i = 0; i < 4; i++) {
		int pilot_mask = 0;
		int chan_mask = 0;
		int bp = 0;

		for (bp = 0; bp < 30; bp++) {
			if ((cur_bin > lower) && (cur_bin < upper)) {
				pilot_mask = pilot_mask | 0x1 << bp;
				chan_mask = chan_mask | 0x1 << bp;
			}
			cur_bin += 100;
		}
		cur_bin += inc[i];
		REG_WRITE(ah, pilot_mask_reg[i], pilot_mask);
		REG_WRITE(ah, chan_mask_reg[i], chan_mask);
	}

	cur_vit_mask = 6100;
	upper = bin + 120;
	lower = bin - 120;

	for (i = 0; i < ARRAY_SIZE(mask_m); i++) {
		if ((cur_vit_mask > lower) && (cur_vit_mask < upper)) {
			/* workaround for gcc bug #37014 */
			volatile int tmp_v = abs(cur_vit_mask - bin);

			if (tmp_v < 75)
				mask_amt = 1;
			else
				mask_amt = 0;
			if (cur_vit_mask < 0)
				mask_m[abs(cur_vit_mask / 100)] = mask_amt;
			else
				mask_p[cur_vit_mask / 100] = mask_amt;
		}
		cur_vit_mask -= 100;
	}

	tmp_mask = (mask_m[46] << 30) | (mask_m[47] << 28)
		| (mask_m[48] << 26) | (mask_m[49] << 24)
		| (mask_m[50] << 22) | (mask_m[51] << 20)
		| (mask_m[52] << 18) | (mask_m[53] << 16)
		| (mask_m[54] << 14) | (mask_m[55] << 12)
		| (mask_m[56] << 10) | (mask_m[57] << 8)
		| (mask_m[58] << 6) | (mask_m[59] << 4)
		| (mask_m[60] << 2) | (mask_m[61] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK_1, tmp_mask);
	REG_WRITE(ah, AR_PHY_VIT_MASK2_M_46_61, tmp_mask);

	tmp_mask = (mask_m[31] << 28)
		| (mask_m[32] << 26) | (mask_m[33] << 24)
		| (mask_m[34] << 22) | (mask_m[35] << 20)
		| (mask_m[36] << 18) | (mask_m[37] << 16)
		| (mask_m[48] << 14) | (mask_m[39] << 12)
		| (mask_m[40] << 10) | (mask_m[41] << 8)
		| (mask_m[42] << 6) | (mask_m[43] << 4)
		| (mask_m[44] << 2) | (mask_m[45] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK_2, tmp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_M_31_45, tmp_mask);

	tmp_mask = (mask_m[16] << 30) | (mask_m[16] << 28)
		| (mask_m[18] << 26) | (mask_m[18] << 24)
		| (mask_m[20] << 22) | (mask_m[20] << 20)
		| (mask_m[22] << 18) | (mask_m[22] << 16)
		| (mask_m[24] << 14) | (mask_m[24] << 12)
		| (mask_m[25] << 10) | (mask_m[26] << 8)
		| (mask_m[27] << 6) | (mask_m[28] << 4)
		| (mask_m[29] << 2) | (mask_m[30] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK_3, tmp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_M_16_30, tmp_mask);

	tmp_mask = (mask_m[0] << 30) | (mask_m[1] << 28)
		| (mask_m[2] << 26) | (mask_m[3] << 24)
		| (mask_m[4] << 22) | (mask_m[5] << 20)
		| (mask_m[6] << 18) | (mask_m[7] << 16)
		| (mask_m[8] << 14) | (mask_m[9] << 12)
		| (mask_m[10] << 10) | (mask_m[11] << 8)
		| (mask_m[12] << 6) | (mask_m[13] << 4)
		| (mask_m[14] << 2) | (mask_m[15] << 0);
	REG_WRITE(ah, AR_PHY_MASK_CTL, tmp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_M_00_15, tmp_mask);

	tmp_mask = (mask_p[15] << 28)
		| (mask_p[14] << 26) | (mask_p[13] << 24)
		| (mask_p[12] << 22) | (mask_p[11] << 20)
		| (mask_p[10] << 18) | (mask_p[9] << 16)
		| (mask_p[8] << 14) | (mask_p[7] << 12)
		| (mask_p[6] << 10) | (mask_p[5] << 8)
		| (mask_p[4] << 6) | (mask_p[3] << 4)
		| (mask_p[2] << 2) | (mask_p[1] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK2_1, tmp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_P_15_01, tmp_mask);

	tmp_mask = (mask_p[30] << 28)
		| (mask_p[29] << 26) | (mask_p[28] << 24)
		| (mask_p[27] << 22) | (mask_p[26] << 20)
		| (mask_p[25] << 18) | (mask_p[24] << 16)
		| (mask_p[23] << 14) | (mask_p[22] << 12)
		| (mask_p[21] << 10) | (mask_p[20] << 8)
		| (mask_p[19] << 6) | (mask_p[18] << 4)
		| (mask_p[17] << 2) | (mask_p[16] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK2_2, tmp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_P_30_16, tmp_mask);

	tmp_mask = (mask_p[45] << 28)
		| (mask_p[44] << 26) | (mask_p[43] << 24)
		| (mask_p[42] << 22) | (mask_p[41] << 20)
		| (mask_p[40] << 18) | (mask_p[39] << 16)
		| (mask_p[38] << 14) | (mask_p[37] << 12)
		| (mask_p[36] << 10) | (mask_p[35] << 8)
		| (mask_p[34] << 6) | (mask_p[33] << 4)
		| (mask_p[32] << 2) | (mask_p[31] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK2_3, tmp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_P_45_31, tmp_mask);

	tmp_mask = (mask_p[61] << 30) | (mask_p[60] << 28)
		| (mask_p[59] << 26) | (mask_p[58] << 24)
		| (mask_p[57] << 22) | (mask_p[56] << 20)
		| (mask_p[55] << 18) | (mask_p[54] << 16)
		| (mask_p[53] << 14) | (mask_p[52] << 12)
		| (mask_p[51] << 10) | (mask_p[50] << 8)
		| (mask_p[49] << 6) | (mask_p[48] << 4)
		| (mask_p[47] << 2) | (mask_p[46] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK2_4, tmp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_P_61_45, tmp_mask);
}