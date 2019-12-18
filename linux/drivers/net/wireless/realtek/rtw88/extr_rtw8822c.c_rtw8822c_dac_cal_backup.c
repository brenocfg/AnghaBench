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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  RF_PATH_A ; 
 int /*<<< orphan*/  RF_PATH_B ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_backup_dck (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_backup_path (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int rtw_read32 (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_write32_clr (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int,int) ; 
 int /*<<< orphan*/  rtw_write32_set (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw8822c_dac_cal_backup(struct rtw_dev *rtwdev)
{
	u32 temp[3];

	temp[0] = rtw_read32(rtwdev, 0x1860);
	temp[1] = rtw_read32(rtwdev, 0x4160);
	temp[2] = rtw_read32(rtwdev, 0x9b4);

	/* set clock */
	rtw_write32(rtwdev, 0x9b4, 0xdb66db00);

	/* backup path-A I/Q */
	rtw_write32_clr(rtwdev, 0x1830, BIT(30));
	rtw_write32_mask(rtwdev, 0x1860, 0xfc000000, 0x3c);
	rtw8822c_dac_cal_backup_path(rtwdev, RF_PATH_A);

	/* backup path-B I/Q */
	rtw_write32_clr(rtwdev, 0x4130, BIT(30));
	rtw_write32_mask(rtwdev, 0x4160, 0xfc000000, 0x3c);
	rtw8822c_dac_cal_backup_path(rtwdev, RF_PATH_B);

	rtw8822c_dac_cal_backup_dck(rtwdev);
	rtw_write32_set(rtwdev, 0x1830, BIT(30));
	rtw_write32_set(rtwdev, 0x4130, BIT(30));

	rtw_write32(rtwdev, 0x1860, temp[0]);
	rtw_write32(rtwdev, 0x4160, temp[1]);
	rtw_write32(rtwdev, 0x9b4, temp[2]);
}