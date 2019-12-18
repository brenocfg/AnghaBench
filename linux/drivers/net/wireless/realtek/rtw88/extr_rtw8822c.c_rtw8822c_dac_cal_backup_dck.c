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
typedef  void* u8 ;
struct rtw_dm_info {void**** dack_dck; } ;
struct rtw_dev {struct rtw_dm_info dm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_DCKA_I_0 ; 
 int /*<<< orphan*/  REG_DCKA_I_1 ; 
 int /*<<< orphan*/  REG_DCKA_Q_0 ; 
 int /*<<< orphan*/  REG_DCKA_Q_1 ; 
 int /*<<< orphan*/  REG_DCKB_I_0 ; 
 int /*<<< orphan*/  REG_DCKB_I_1 ; 
 int /*<<< orphan*/  REG_DCKB_Q_0 ; 
 int /*<<< orphan*/  REG_DCKB_Q_1 ; 
 size_t RF_PATH_A ; 
 size_t RF_PATH_B ; 
 scalar_t__ rtw_read32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822c_dac_cal_backup_dck(struct rtw_dev *rtwdev)
{
	struct rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 val;

	val = (u8)rtw_read32_mask(rtwdev, REG_DCKA_I_0, 0xf0000000);
	dm_info->dack_dck[RF_PATH_A][0][0] = val;
	val = (u8)rtw_read32_mask(rtwdev, REG_DCKA_I_1, 0xf);
	dm_info->dack_dck[RF_PATH_A][0][1] = val;
	val = (u8)rtw_read32_mask(rtwdev, REG_DCKA_Q_0, 0xf0000000);
	dm_info->dack_dck[RF_PATH_A][1][0] = val;
	val = (u8)rtw_read32_mask(rtwdev, REG_DCKA_Q_1, 0xf);
	dm_info->dack_dck[RF_PATH_A][1][1] = val;

	val = (u8)rtw_read32_mask(rtwdev, REG_DCKB_I_0, 0xf0000000);
	dm_info->dack_dck[RF_PATH_B][0][0] = val;
	val = (u8)rtw_read32_mask(rtwdev, REG_DCKB_I_1, 0xf);
	dm_info->dack_dck[RF_PATH_B][1][0] = val;
	val = (u8)rtw_read32_mask(rtwdev, REG_DCKB_Q_0, 0xf0000000);
	dm_info->dack_dck[RF_PATH_B][0][1] = val;
	val = (u8)rtw_read32_mask(rtwdev, REG_DCKB_Q_1, 0xf);
	dm_info->dack_dck[RF_PATH_B][1][1] = val;
}