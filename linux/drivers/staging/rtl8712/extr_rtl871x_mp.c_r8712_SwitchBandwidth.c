#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int curr_bandwidth; } ;
struct _adapter {TYPE_1__ mppriv; } ;

/* Variables and functions */
 int BIT (int) ; 
 int HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
#define  HT_CHANNEL_WIDTH_20 129 
#define  HT_CHANNEL_WIDTH_40 128 
 int /*<<< orphan*/  RF_CHNLBW ; 
 int /*<<< orphan*/  RF_PATH_A ; 
 int bCCKSideBand ; 
 int bMaskDWord ; 
 int bRFMOD ; 
 int r8712_read8 (struct _adapter*,int) ; 
 int /*<<< orphan*/  r8712_write8 (struct _adapter*,int,int) ; 
 int /*<<< orphan*/  rCCK0_System ; 
 int /*<<< orphan*/  rFPGA0_AnalogParameter2 ; 
 int /*<<< orphan*/  rFPGA0_RFMOD ; 
 int /*<<< orphan*/  rFPGA1_RFMOD ; 
 int /*<<< orphan*/  rOFDM1_LSTF ; 
 int /*<<< orphan*/  set_bb_reg (struct _adapter*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_rf_reg (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void r8712_SwitchBandwidth(struct _adapter *pAdapter)
{
	/* 3 1.Set MAC register : BWOPMODE  bit2:1 20MhzBW */
	u8 regBwOpMode = 0;
	u8 Bandwidth = pAdapter->mppriv.curr_bandwidth;

	regBwOpMode = r8712_read8(pAdapter, 0x10250203);
	if (Bandwidth == HT_CHANNEL_WIDTH_20)
		regBwOpMode |= BIT(2);
	else
		regBwOpMode &= ~(BIT(2));
	r8712_write8(pAdapter, 0x10250203, regBwOpMode);
	/* 3 2.Set PHY related register */
	switch (Bandwidth) {
	/* 20 MHz channel*/
	case HT_CHANNEL_WIDTH_20:
		set_bb_reg(pAdapter, rFPGA0_RFMOD, bRFMOD, 0x0);
		set_bb_reg(pAdapter, rFPGA1_RFMOD, bRFMOD, 0x0);
		/* Use PHY_REG.txt default value. Do not need to change.
		 * Correct the tx power for CCK rate in 40M.
		 * It is set in Tx descriptor for 8192x series
		 */
		set_bb_reg(pAdapter, rFPGA0_AnalogParameter2, bMaskDWord, 0x58);
		break;
	/* 40 MHz channel*/
	case HT_CHANNEL_WIDTH_40:
		set_bb_reg(pAdapter, rFPGA0_RFMOD, bRFMOD, 0x1);
		set_bb_reg(pAdapter, rFPGA1_RFMOD, bRFMOD, 0x1);
		/* Use PHY_REG.txt default value. Do not need to change.
		 * Correct the tx power for CCK rate in 40M.
		 * Set Control channel to upper or lower. These settings are
		 * required only for 40MHz
		 */
		set_bb_reg(pAdapter, rCCK0_System, bCCKSideBand,
			   (HAL_PRIME_CHNL_OFFSET_DONT_CARE >> 1));
		set_bb_reg(pAdapter, rOFDM1_LSTF, 0xC00,
			   HAL_PRIME_CHNL_OFFSET_DONT_CARE);
		set_bb_reg(pAdapter, rFPGA0_AnalogParameter2, bMaskDWord, 0x18);
		break;
	default:
		break;
	}

	/* 3 3.Set RF related register */
	switch (Bandwidth) {
	case HT_CHANNEL_WIDTH_20:
		set_rf_reg(pAdapter, RF_PATH_A, RF_CHNLBW,
			   BIT(10) | BIT(11), 0x01);
		break;
	case HT_CHANNEL_WIDTH_40:
		set_rf_reg(pAdapter, RF_PATH_A, RF_CHNLBW,
			   BIT(10) | BIT(11), 0x00);
		break;
	default:
		break;
	}
}