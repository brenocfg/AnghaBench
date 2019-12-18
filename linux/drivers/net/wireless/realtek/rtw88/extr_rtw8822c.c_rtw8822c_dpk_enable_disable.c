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
typedef  int u32 ;
struct rtw_dpk_info {int is_dpk_pwr_on; int /*<<< orphan*/ * dpk_gs; int /*<<< orphan*/  dpk_path_ok; } ;
struct TYPE_2__ {struct rtw_dpk_info dpk_info; } ;
struct rtw_dev {TYPE_1__ dm_info; } ;

/* Variables and functions */
 int BIT (int) ; 
 int BIT_DPD_EN ; 
 int BIT_SUBPAGE ; 
 int /*<<< orphan*/  REG_DPD_CTL0_S0 ; 
 int /*<<< orphan*/  REG_DPD_CTL0_S1 ; 
 int /*<<< orphan*/  REG_DPD_CTL1_S0 ; 
 int /*<<< orphan*/  REG_DPD_CTL1_S1 ; 
 int /*<<< orphan*/  REG_NCTL0 ; 
 size_t RF_PATH_A ; 
 size_t RF_PATH_B ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw8822c_dpk_enable_disable(struct rtw_dev *rtwdev)
{
	struct rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u32 mask = BIT(15) | BIT(14);

	rtw_write32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0xc);

	rtw_write32_mask(rtwdev, REG_DPD_CTL1_S0, BIT_DPD_EN,
			 dpk_info->is_dpk_pwr_on);
	rtw_write32_mask(rtwdev, REG_DPD_CTL1_S1, BIT_DPD_EN,
			 dpk_info->is_dpk_pwr_on);

	if (test_bit(RF_PATH_A, dpk_info->dpk_path_ok)) {
		rtw_write32_mask(rtwdev, REG_DPD_CTL1_S0, mask, 0x0);
		rtw_write8(rtwdev, REG_DPD_CTL0_S0, dpk_info->dpk_gs[RF_PATH_A]);
	}
	if (test_bit(RF_PATH_B, dpk_info->dpk_path_ok)) {
		rtw_write32_mask(rtwdev, REG_DPD_CTL1_S1, mask, 0x0);
		rtw_write8(rtwdev, REG_DPD_CTL0_S1, dpk_info->dpk_gs[RF_PATH_B]);
	}
}