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
typedef  int /*<<< orphan*/  u32 ;
struct rtw_dm_info {scalar_t__*** dack_msbk; } ;
struct rtw_dev {struct rtw_dm_info dm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 size_t RF_PATH_A ; 
 size_t RF_PATH_B ; 
 int /*<<< orphan*/  __rtw8822c_dac_cal_restore (struct rtw_dev*) ; 
 int /*<<< orphan*/  check_hw_ready (struct rtw_dev*,int,int,int) ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_restore_prepare (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int /*<<< orphan*/  rtw_read32 (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool rtw8822c_dac_cal_restore(struct rtw_dev *rtwdev)
{
	struct rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 temp[3];

	/* sample the first element for both path's IQ vector */
	if (dm_info->dack_msbk[RF_PATH_A][0][0] == 0 &&
	    dm_info->dack_msbk[RF_PATH_A][1][0] == 0 &&
	    dm_info->dack_msbk[RF_PATH_B][0][0] == 0 &&
	    dm_info->dack_msbk[RF_PATH_B][1][0] == 0)
		return false;

	temp[0] = rtw_read32(rtwdev, 0x1860);
	temp[1] = rtw_read32(rtwdev, 0x4160);
	temp[2] = rtw_read32(rtwdev, 0x9b4);

	rtw8822c_dac_cal_restore_prepare(rtwdev);
	if (!check_hw_ready(rtwdev, 0x2808, 0x7fff80, 0xffff) ||
	    !check_hw_ready(rtwdev, 0x2834, 0x7fff80, 0xffff) ||
	    !check_hw_ready(rtwdev, 0x4508, 0x7fff80, 0xffff) ||
	    !check_hw_ready(rtwdev, 0x4534, 0x7fff80, 0xffff))
		return false;

	if (!__rtw8822c_dac_cal_restore(rtwdev)) {
		rtw_err(rtwdev, "failed to restore dack vectors\n");
		return false;
	}

	rtw_write32_mask(rtwdev, 0x1830, BIT(30), 0x1);
	rtw_write32_mask(rtwdev, 0x4130, BIT(30), 0x1);
	rtw_write32(rtwdev, 0x1860, temp[0]);
	rtw_write32(rtwdev, 0x4160, temp[1]);
	rtw_write32_mask(rtwdev, 0x18b0, BIT(27), 0x1);
	rtw_write32_mask(rtwdev, 0x18cc, BIT(27), 0x1);
	rtw_write32_mask(rtwdev, 0x41b0, BIT(27), 0x1);
	rtw_write32_mask(rtwdev, 0x41cc, BIT(27), 0x1);
	rtw_write32(rtwdev, 0x9b4, temp[2]);

	return true;
}