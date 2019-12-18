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
typedef  scalar_t__ u32 ;
struct rtw_dm_info {scalar_t__* igi_history; scalar_t__ min_rssi; scalar_t__ cck_fa_avg; } ;
struct rtw_dev {struct rtw_dm_info dm_info; } ;

/* Variables and functions */
 scalar_t__ CCK_PD_FA_LV0_MAX ; 
 scalar_t__ CCK_PD_FA_LV1_MIN ; 
 scalar_t__ CCK_PD_IGI_LV2_VAL ; 
 scalar_t__ CCK_PD_IGI_LV3_VAL ; 
 scalar_t__ CCK_PD_IGI_LV4_VAL ; 
 scalar_t__ CCK_PD_LV_MAX ; 
 scalar_t__ CCK_PD_RSSI_LV2_VAL ; 
 scalar_t__ CCK_PD_RSSI_LV3_VAL ; 
 scalar_t__ CCK_PD_RSSI_LV4_VAL ; 

__attribute__((used)) static u8 rtw_phy_cck_pd_lv_link(struct rtw_dev *rtwdev)
{
	struct rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 igi = dm_info->igi_history[0];
	u8 rssi = dm_info->min_rssi;
	u32 cck_fa_avg = dm_info->cck_fa_avg;

	if (igi > CCK_PD_IGI_LV4_VAL && rssi > CCK_PD_RSSI_LV4_VAL)
		return 4;
	if (igi > CCK_PD_IGI_LV3_VAL && rssi > CCK_PD_RSSI_LV3_VAL)
		return 3;
	if (igi > CCK_PD_IGI_LV2_VAL || rssi > CCK_PD_RSSI_LV2_VAL)
		return 2;
	if (cck_fa_avg > CCK_PD_FA_LV1_MIN)
		return 1;
	if (cck_fa_avg < CCK_PD_FA_LV0_MAX)
		return 0;

	return CCK_PD_LV_MAX;
}