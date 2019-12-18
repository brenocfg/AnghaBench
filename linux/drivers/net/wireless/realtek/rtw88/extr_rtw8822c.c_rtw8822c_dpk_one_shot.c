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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int BIT_IQ_SWITCH ; 
 int BIT_RPT_SEL ; 
 int BIT_SUBPAGE ; 
 int /*<<< orphan*/  REG_DPD_CTL0 ; 
 int /*<<< orphan*/  REG_NCTL0 ; 
 int /*<<< orphan*/  REG_RXSRAM_CTL ; 
 int /*<<< orphan*/  REG_R_CONFIG ; 
 int REG_STAT_RPT ; 
 int /*<<< orphan*/  RTW_DBG_RFK ; 
 scalar_t__ RTW_DPK_CAL_PWR ; 
 int /*<<< orphan*/  check_hw_ready (struct rtw_dev*,int,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ rtw8822c_dpk_get_cmd (struct rtw_dev*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rtw8822c_dpk_set_gnt_wl (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int,int) ; 

__attribute__((used)) static u8 rtw8822c_dpk_one_shot(struct rtw_dev *rtwdev, u8 path, u8 action)
{
	u16 dpk_cmd;
	u8 result = 0;

	rtw8822c_dpk_set_gnt_wl(rtwdev, true);

	if (action == RTW_DPK_CAL_PWR) {
		rtw_write32_mask(rtwdev, REG_DPD_CTL0, BIT(12), 0x1);
		rtw_write32_mask(rtwdev, REG_DPD_CTL0, BIT(12), 0x0);
		rtw_write32_mask(rtwdev, REG_RXSRAM_CTL, BIT_RPT_SEL, 0x0);
		msleep(10);
		if (!check_hw_ready(rtwdev, REG_STAT_RPT, BIT(31), 0x1)) {
			result = 1;
			rtw_dbg(rtwdev, RTW_DBG_RFK, "[DPK] one-shot over 20ms\n");
		}
	} else {
		rtw_write32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE,
				 0x8 | (path << 1));
		rtw_write32_mask(rtwdev, REG_R_CONFIG, BIT_IQ_SWITCH, 0x9);

		dpk_cmd = rtw8822c_dpk_get_cmd(rtwdev, action, path);
		rtw_write32(rtwdev, REG_NCTL0, dpk_cmd);
		rtw_write32(rtwdev, REG_NCTL0, dpk_cmd + 1);
		msleep(10);
		if (!check_hw_ready(rtwdev, 0x2d9c, 0xff, 0x55)) {
			result = 1;
			rtw_dbg(rtwdev, RTW_DBG_RFK, "[DPK] one-shot over 20ms\n");
		}
		rtw_write32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE,
				 0x8 | (path << 1));
		rtw_write32_mask(rtwdev, REG_R_CONFIG, BIT_IQ_SWITCH, 0x0);
	}

	rtw8822c_dpk_set_gnt_wl(rtwdev, false);

	rtw_write8(rtwdev, 0x1b10, 0x0);

	return result;
}