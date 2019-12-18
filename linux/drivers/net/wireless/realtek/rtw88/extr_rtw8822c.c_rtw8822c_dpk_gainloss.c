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
typedef  scalar_t__ u32 ;
struct rtw_dpk_info {int /*<<< orphan*/ * thermal_dpk_delta; } ;
struct TYPE_2__ {struct rtw_dpk_info dpk_info; } ;
struct rtw_dev {TYPE_1__ dm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_GAIN_TXBB ; 
 int /*<<< orphan*/  BIT_TXAGC ; 
 int /*<<< orphan*/  RF_MODE_TRXAGC ; 
 int /*<<< orphan*/  RF_TX_GAIN ; 
 int /*<<< orphan*/  RTW_DPK_DAGC ; 
 int /*<<< orphan*/  abs (scalar_t__) ; 
 scalar_t__ rtw8822c_dpk_dc_corr_check (struct rtw_dev*,scalar_t__) ; 
 int /*<<< orphan*/  rtw8822c_dpk_dgain_read (struct rtw_dev*,scalar_t__) ; 
 scalar_t__ rtw8822c_dpk_gainloss_result (struct rtw_dev*,scalar_t__) ; 
 int /*<<< orphan*/  rtw8822c_dpk_one_shot (struct rtw_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw8822c_dpk_pas_agc (struct rtw_dev*,scalar_t__,int,int) ; 
 scalar_t__ rtw8822c_dpk_rf_setting (struct rtw_dev*,scalar_t__) ; 
 int /*<<< orphan*/  rtw8822c_dpk_rxbb_dc_cal (struct rtw_dev*,scalar_t__) ; 
 scalar_t__ rtw8822c_dpk_thermal_read (struct rtw_dev*,scalar_t__) ; 
 scalar_t__ rtw_read_rf (struct rtw_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write_rf (struct rtw_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u32 rtw8822c_dpk_gainloss(struct rtw_dev *rtwdev, u8 path)
{
	struct rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u8 tx_agc, tx_bb, ori_txbb, ori_txagc, tx_agc_search, t1, t2;

	ori_txbb = rtw8822c_dpk_rf_setting(rtwdev, path);
	ori_txagc = (u8)rtw_read_rf(rtwdev, path, RF_MODE_TRXAGC, BIT_TXAGC);

	rtw8822c_dpk_rxbb_dc_cal(rtwdev, path);
	rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_DAGC);
	rtw8822c_dpk_dgain_read(rtwdev, path);

	if (rtw8822c_dpk_dc_corr_check(rtwdev, path)) {
		rtw8822c_dpk_rxbb_dc_cal(rtwdev, path);
		rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_DAGC);
		rtw8822c_dpk_dc_corr_check(rtwdev, path);
	}

	t1 = rtw8822c_dpk_thermal_read(rtwdev, path);
	tx_bb = rtw8822c_dpk_pas_agc(rtwdev, path, false, true);
	tx_agc_search = rtw8822c_dpk_gainloss_result(rtwdev, path);

	if (tx_bb < tx_agc_search)
		tx_bb = 0;
	else
		tx_bb = tx_bb - tx_agc_search;

	rtw_write_rf(rtwdev, path, RF_TX_GAIN, BIT_GAIN_TXBB, tx_bb);

	tx_agc = ori_txagc - (ori_txbb - tx_bb);

	t2 = rtw8822c_dpk_thermal_read(rtwdev, path);

	dpk_info->thermal_dpk_delta[path] = abs(t2 - t1);

	return tx_agc;
}