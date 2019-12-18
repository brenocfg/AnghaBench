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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rtw_dm_info {int cck_fa_cnt; int cck_fa_avg; } ;
struct TYPE_3__ {scalar_t__ current_band_type; } ;
struct rtw_dev {TYPE_1__ hal; struct rtw_chip_info* chip; struct rtw_dm_info dm_info; } ;
struct rtw_chip_info {TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cck_pd_set ) (struct rtw_dev*,scalar_t__) ;} ;

/* Variables and functions */
 int CCK_FA_AVG_RESET ; 
 scalar_t__ CCK_PD_LV_MAX ; 
 scalar_t__ RTW_BAND_2G ; 
 scalar_t__ rtw_phy_cck_pd_lv (struct rtw_dev*) ; 
 int /*<<< orphan*/  stub1 (struct rtw_dev*,scalar_t__) ; 

__attribute__((used)) static void rtw_phy_cck_pd(struct rtw_dev *rtwdev)
{
	struct rtw_dm_info *dm_info = &rtwdev->dm_info;
	struct rtw_chip_info *chip = rtwdev->chip;
	u32 cck_fa = dm_info->cck_fa_cnt;
	u8 level;

	if (rtwdev->hal.current_band_type != RTW_BAND_2G)
		return;

	if (dm_info->cck_fa_avg == CCK_FA_AVG_RESET)
		dm_info->cck_fa_avg = cck_fa;
	else
		dm_info->cck_fa_avg = (dm_info->cck_fa_avg * 3 + cck_fa) >> 2;

	level = rtw_phy_cck_pd_lv(rtwdev);

	if (level >= CCK_PD_LV_MAX)
		return;

	if (chip->ops->cck_pd_set)
		chip->ops->cck_pd_set(rtwdev, level);
}