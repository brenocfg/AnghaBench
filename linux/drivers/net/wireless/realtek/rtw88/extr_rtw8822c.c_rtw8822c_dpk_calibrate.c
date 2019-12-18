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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtw_dpk_info {int /*<<< orphan*/  dpk_path_ok; scalar_t__* result; } ;
struct TYPE_2__ {struct rtw_dpk_info dpk_info; } ;
struct rtw_dev {TYPE_1__ dm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_DBG_RFK ; 
 size_t rtw8822c_dpk_by_path (struct rtw_dev*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  rtw8822c_dpk_check_pass (struct rtw_dev*,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  rtw8822c_dpk_gainloss (struct rtw_dev*,size_t) ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw8822c_dpk_calibrate(struct rtw_dev *rtwdev, u8 path)
{
	struct rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u32 dpk_txagc;
	u8 dpk_fail;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DPK] s%d dpk start\n", path);

	dpk_txagc = rtw8822c_dpk_gainloss(rtwdev, path);

	dpk_fail = rtw8822c_dpk_by_path(rtwdev, dpk_txagc, path);

	if (!rtw8822c_dpk_check_pass(rtwdev, dpk_fail, dpk_txagc, path))
		rtw_err(rtwdev, "failed to do dpk calibration\n");

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DPK] s%d dpk finish\n", path);

	if (dpk_info->result[path])
		set_bit(path, dpk_info->dpk_path_ok);
}