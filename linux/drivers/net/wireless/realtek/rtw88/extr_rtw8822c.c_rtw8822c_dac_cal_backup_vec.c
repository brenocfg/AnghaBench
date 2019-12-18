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
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct rtw_dm_info {scalar_t__*** dack_msbk; } ;
struct rtw_dev {struct rtw_dm_info dm_info; } ;

/* Variables and functions */
 size_t DACK_MSBK_BACKUP_NUM ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ rtw_read32_mask (struct rtw_dev*,size_t,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,size_t,int,size_t) ; 

__attribute__((used)) static void rtw8822c_dac_cal_backup_vec(struct rtw_dev *rtwdev,
					u8 path, u8 vec, u32 w_addr, u32 r_addr)
{
	struct rtw_dm_info *dm_info = &rtwdev->dm_info;
	u16 val;
	u32 i;

	if (WARN_ON(vec >= 2))
		return;

	for (i = 0; i < DACK_MSBK_BACKUP_NUM; i++) {
		rtw_write32_mask(rtwdev, w_addr, 0xf0000000, i);
		val = (u16)rtw_read32_mask(rtwdev, r_addr, 0x7fc0000);
		dm_info->dack_msbk[path][vec][i] = val;
	}
}