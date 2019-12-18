#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {scalar_t__ dpk_band; } ;
struct TYPE_5__ {TYPE_1__ dpk_info; } ;
struct TYPE_6__ {int rf_path_num; } ;
struct rtw_dev {TYPE_2__ dm_info; TYPE_3__ hal; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_GLOSS_DB ; 
 int /*<<< orphan*/  BIT_SUBPAGE ; 
 int /*<<< orphan*/  BIT_TX_CFIR ; 
 int /*<<< orphan*/  REG_DPD_CTL11 ; 
 int /*<<< orphan*/  REG_DPD_CTL12 ; 
 int /*<<< orphan*/  REG_DPD_LUT0 ; 
 int /*<<< orphan*/  REG_DPD_LUT3 ; 
 int /*<<< orphan*/  REG_IQK_CTL1 ; 
 int /*<<< orphan*/  REG_NCTL0 ; 
 int /*<<< orphan*/  RFREG_MASK ; 
 int /*<<< orphan*/  RF_RXAGC_OFFSET ; 
 scalar_t__ RTW_BAND_2G ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write_rf (struct rtw_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822c_dpk_pre_setting(struct rtw_dev *rtwdev)
{
	u8 path;

	for (path = 0; path < rtwdev->hal.rf_path_num; path++) {
		rtw_write_rf(rtwdev, path, RF_RXAGC_OFFSET, RFREG_MASK, 0x0);
		rtw_write32(rtwdev, REG_NCTL0, 0x8 | (path << 1));
		if (rtwdev->dm_info.dpk_info.dpk_band == RTW_BAND_2G)
			rtw_write32(rtwdev, REG_DPD_LUT3, 0x1f100000);
		else
			rtw_write32(rtwdev, REG_DPD_LUT3, 0x1f0d0000);
		rtw_write32_mask(rtwdev, REG_DPD_LUT0, BIT_GLOSS_DB, 0x4);
		rtw_write32_mask(rtwdev, REG_IQK_CTL1, BIT_TX_CFIR, 0x3);
	}
	rtw_write32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0xc);
	rtw_write32(rtwdev, REG_DPD_CTL11, 0x3b23170b);
	rtw_write32(rtwdev, REG_DPD_CTL12, 0x775f5347);
}