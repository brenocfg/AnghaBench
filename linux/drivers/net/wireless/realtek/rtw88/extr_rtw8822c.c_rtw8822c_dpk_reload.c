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
typedef  scalar_t__ u8 ;
struct rtw_dpk_info {int is_reload; scalar_t__ dpk_ch; } ;
struct TYPE_2__ {struct rtw_dpk_info dpk_info; } ;
struct rtw_dev {TYPE_1__ dm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFREG_MASK ; 
 int /*<<< orphan*/  RF_PATH_A ; 
 int /*<<< orphan*/  RTW_DBG_RFK ; 
 int /*<<< orphan*/  rtw8822c_dpk_reload_data (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int rtw_read_rf (struct rtw_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rtw8822c_dpk_reload(struct rtw_dev *rtwdev)
{
	struct rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u8 channel;

	dpk_info->is_reload = false;

	channel = (u8)(rtw_read_rf(rtwdev, RF_PATH_A, 0x18, RFREG_MASK) & 0xff);

	if (channel == dpk_info->dpk_ch) {
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[DPK] DPK reload for CH%d!!\n", dpk_info->dpk_ch);
		rtw8822c_dpk_reload_data(rtwdev);
		dpk_info->is_reload = true;
	}

	return dpk_info->is_reload;
}