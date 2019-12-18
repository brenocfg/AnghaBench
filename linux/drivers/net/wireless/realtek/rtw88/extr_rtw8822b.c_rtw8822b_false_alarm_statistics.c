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
typedef  int u32 ;
struct rtw_dm_info {int cck_fa_cnt; int ofdm_fa_cnt; int total_fa_cnt; int cck_ok_cnt; int cck_err_cnt; int ofdm_ok_cnt; int ofdm_err_cnt; int ht_ok_cnt; int ht_err_cnt; int vht_ok_cnt; int vht_err_cnt; } ;
struct rtw_dev {struct rtw_dm_info dm_info; } ;

/* Variables and functions */
 int BIT (int) ; 
 int rtw_read16 (struct rtw_dev*,int) ; 
 int rtw_read32 (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_write32_clr (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_write32_set (struct rtw_dev*,int,int) ; 

__attribute__((used)) static void rtw8822b_false_alarm_statistics(struct rtw_dev *rtwdev)
{
	struct rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 cck_enable;
	u32 cck_fa_cnt;
	u32 ofdm_fa_cnt;
	u32 crc32_cnt;

	cck_enable = rtw_read32(rtwdev, 0x808) & BIT(28);
	cck_fa_cnt = rtw_read16(rtwdev, 0xa5c);
	ofdm_fa_cnt = rtw_read16(rtwdev, 0xf48);

	dm_info->cck_fa_cnt = cck_fa_cnt;
	dm_info->ofdm_fa_cnt = ofdm_fa_cnt;
	dm_info->total_fa_cnt = ofdm_fa_cnt;
	dm_info->total_fa_cnt += cck_enable ? cck_fa_cnt : 0;

	crc32_cnt = rtw_read32(rtwdev, 0xf04);
	dm_info->cck_ok_cnt = crc32_cnt & 0xffff;
	dm_info->cck_err_cnt = (crc32_cnt & 0xffff0000) >> 16;
	crc32_cnt = rtw_read32(rtwdev, 0xf14);
	dm_info->ofdm_ok_cnt = crc32_cnt & 0xffff;
	dm_info->ofdm_err_cnt = (crc32_cnt & 0xffff0000) >> 16;
	crc32_cnt = rtw_read32(rtwdev, 0xf10);
	dm_info->ht_ok_cnt = crc32_cnt & 0xffff;
	dm_info->ht_err_cnt = (crc32_cnt & 0xffff0000) >> 16;
	crc32_cnt = rtw_read32(rtwdev, 0xf0c);
	dm_info->vht_ok_cnt = crc32_cnt & 0xffff;
	dm_info->vht_err_cnt = (crc32_cnt & 0xffff0000) >> 16;

	rtw_write32_set(rtwdev, 0x9a4, BIT(17));
	rtw_write32_clr(rtwdev, 0x9a4, BIT(17));
	rtw_write32_clr(rtwdev, 0xa2c, BIT(15));
	rtw_write32_set(rtwdev, 0xa2c, BIT(15));
	rtw_write32_set(rtwdev, 0xb58, BIT(0));
	rtw_write32_clr(rtwdev, 0xb58, BIT(0));
}