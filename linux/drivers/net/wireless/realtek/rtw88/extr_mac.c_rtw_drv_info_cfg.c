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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BIT_APP_PHYSTS ; 
 int PHY_STATUS_SIZE ; 
 int /*<<< orphan*/  REG_RCR ; 
 scalar_t__ REG_RX_DRVINFO_SZ ; 
 scalar_t__ REG_TRXFF_BNDY ; 
 scalar_t__ REG_WMAC_OPTION_FUNCTION ; 
 int rtw_read8 (struct rtw_dev*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_write32_clr (struct rtw_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtw_write32_set (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,scalar_t__,int) ; 

__attribute__((used)) static int rtw_drv_info_cfg(struct rtw_dev *rtwdev)
{
	u8 value8;

	rtw_write8(rtwdev, REG_RX_DRVINFO_SZ, PHY_STATUS_SIZE);
	value8 = rtw_read8(rtwdev, REG_TRXFF_BNDY + 1);
	value8 &= 0xF0;
	/* For rxdesc len = 0 issue */
	value8 |= 0xF;
	rtw_write8(rtwdev, REG_TRXFF_BNDY + 1, value8);
	rtw_write32_set(rtwdev, REG_RCR, BIT_APP_PHYSTS);
	rtw_write32_clr(rtwdev, REG_WMAC_OPTION_FUNCTION + 4, BIT(8) | BIT(9));

	return 0;
}