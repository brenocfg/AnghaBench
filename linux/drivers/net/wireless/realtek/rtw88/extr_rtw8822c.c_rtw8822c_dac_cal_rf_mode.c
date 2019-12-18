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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int DACK_SN_8822C ; 
 int /*<<< orphan*/  RFREG_MASK ; 
 int /*<<< orphan*/  RF_PATH_A ; 
 int /*<<< orphan*/  RF_PATH_B ; 
 int /*<<< orphan*/  RTW_DBG_RFK ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_iq_sample (struct rtw_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_iq_search (struct rtw_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_read_rf (struct rtw_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw8822c_dac_cal_rf_mode(struct rtw_dev *rtwdev,
				     u32 *i_value, u32 *q_value)
{
	u32 iv[DACK_SN_8822C], qv[DACK_SN_8822C];
	u32 rf_a, rf_b;

	rf_a = rtw_read_rf(rtwdev, RF_PATH_A, 0x0, RFREG_MASK);
	rf_b = rtw_read_rf(rtwdev, RF_PATH_B, 0x0, RFREG_MASK);

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] RF path-A=0x%05x\n", rf_a);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] RF path-B=0x%05x\n", rf_b);

	rtw8822c_dac_cal_iq_sample(rtwdev, iv, qv);
	rtw8822c_dac_cal_iq_search(rtwdev, iv, qv, i_value, q_value);
}