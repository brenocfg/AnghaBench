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

/* Variables and functions */
 int REG_TXPAUSE ; 
 int /*<<< orphan*/  RF_AC ; 
 int /*<<< orphan*/  RF_CHNLBW ; 
 int /*<<< orphan*/  RF_PATH_A ; 
 int /*<<< orphan*/  RF_PATH_B ; 
 int /*<<< orphan*/  bMask12Bits ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  phy_set_rf_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rtw_hal_read_rfreg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_read8 (struct adapter*,int) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int,int) ; 

__attribute__((used)) static void phy_lc_calibrate(struct adapter *adapt, bool is2t)
{
	u8 tmpreg;
	u32 rf_a_mode = 0, rf_b_mode = 0, lc_cal;

	/* Check continuous TX and Packet TX */
	tmpreg = usb_read8(adapt, 0xd03);

	if ((tmpreg&0x70) != 0)
		usb_write8(adapt, 0xd03, tmpreg&0x8F);
	else
		usb_write8(adapt, REG_TXPAUSE, 0xFF);

	if ((tmpreg&0x70) != 0) {
		/* 1. Read original RF mode */
		/* Path-A */
		rf_a_mode = rtw_hal_read_rfreg(adapt, RF_PATH_A, RF_AC,
					     bMask12Bits);

		/* Path-B */
		if (is2t)
			rf_b_mode = rtw_hal_read_rfreg(adapt, RF_PATH_B, RF_AC,
						     bMask12Bits);

		/* 2. Set RF mode = standby mode */
		/* Path-A */
		phy_set_rf_reg(adapt, RF_PATH_A, RF_AC, bMask12Bits,
			       (rf_a_mode&0x8FFFF)|0x10000);

		/* Path-B */
		if (is2t)
			phy_set_rf_reg(adapt, RF_PATH_B, RF_AC, bMask12Bits,
				       (rf_b_mode&0x8FFFF)|0x10000);
	}

	/* 3. Read RF reg18 */
	lc_cal = rtw_hal_read_rfreg(adapt, RF_PATH_A, RF_CHNLBW, bMask12Bits);

	/* 4. Set LC calibration begin bit15 */
	phy_set_rf_reg(adapt, RF_PATH_A, RF_CHNLBW, bMask12Bits,
		       lc_cal|0x08000);

	msleep(100);

	/* Restore original situation */
	if ((tmpreg&0x70) != 0) {
		/* Deal with continuous TX case */
		/* Path-A */
		usb_write8(adapt, 0xd03, tmpreg);
		phy_set_rf_reg(adapt, RF_PATH_A, RF_AC, bMask12Bits, rf_a_mode);

		/* Path-B */
		if (is2t)
			phy_set_rf_reg(adapt, RF_PATH_B, RF_AC, bMask12Bits,
				       rf_b_mode);
	} else {
		/* Deal with Packet TX case */
		usb_write8(adapt, REG_TXPAUSE, 0x00);
	}
}