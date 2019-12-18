#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtw_dpk_info {scalar_t__ dpk_ch; scalar_t__ dpk_band; int* dpk_gs; int /*<<< orphan*/  dpk_path_ok; int /*<<< orphan*/ * dpk_txagc; } ;
struct TYPE_4__ {int rf_path_num; } ;
struct TYPE_3__ {struct rtw_dpk_info dpk_info; } ;
struct rtw_dev {TYPE_2__ hal; TYPE_1__ dm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_GS_PWSF ; 
 int /*<<< orphan*/  BIT_SUBPAGE ; 
 int /*<<< orphan*/  REG_DPD_AGC ; 
 int /*<<< orphan*/  REG_DPD_CTL0_S0 ; 
 int /*<<< orphan*/  REG_DPD_CTL0_S1 ; 
 int /*<<< orphan*/  REG_DPD_LUT3 ; 
 int /*<<< orphan*/  REG_NCTL0 ; 
 int RF_PATH_A ; 
 int RF_PATH_B ; 
 scalar_t__ RTW_BAND_2G ; 
 int /*<<< orphan*/  RTW_DPK_DPK_ON ; 
 int /*<<< orphan*/  rtw8822c_dpk_cal_coef1 (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw8822c_dpk_coef_write (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw8822c_dpk_one_shot (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw8822c_dpk_reload_data(struct rtw_dev *rtwdev)
{
	struct rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u8 path;

	if (!test_bit(RF_PATH_A, dpk_info->dpk_path_ok) &&
	    !test_bit(RF_PATH_B, dpk_info->dpk_path_ok) &&
	    dpk_info->dpk_ch == 0)
		return;

	for (path = 0; path < rtwdev->hal.rf_path_num; path++) {
		rtw_write32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE,
				 0x8 | (path << 1));
		if (dpk_info->dpk_band == RTW_BAND_2G)
			rtw_write32(rtwdev, REG_DPD_LUT3, 0x1f100000);
		else
			rtw_write32(rtwdev, REG_DPD_LUT3, 0x1f0d0000);

		rtw_write8(rtwdev, REG_DPD_AGC, dpk_info->dpk_txagc[path]);

		rtw8822c_dpk_coef_write(rtwdev, path,
					test_bit(path, dpk_info->dpk_path_ok));

		rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_DPK_ON);

		rtw_write32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0xc);

		if (path == RF_PATH_A)
			rtw_write32_mask(rtwdev, REG_DPD_CTL0_S0, BIT_GS_PWSF,
					 dpk_info->dpk_gs[path]);
		else
			rtw_write32_mask(rtwdev, REG_DPD_CTL0_S1, BIT_GS_PWSF,
					 dpk_info->dpk_gs[path]);
	}
	rtw8822c_dpk_cal_coef1(rtwdev);
}