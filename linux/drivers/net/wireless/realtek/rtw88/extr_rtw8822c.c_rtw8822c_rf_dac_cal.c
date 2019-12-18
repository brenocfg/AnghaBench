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
struct rtw_backup_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int DACK_PATH_8822C ; 
 int DACK_REG_8822C ; 
 int DACK_RF_8822C ; 
 int /*<<< orphan*/  RF_PATH_A ; 
 int /*<<< orphan*/  RF_PATH_B ; 
 int /*<<< orphan*/  RTW_DBG_RFK ; 
 int /*<<< orphan*/  rtw8822c_dac_backup_reg (struct rtw_dev*,struct rtw_backup_info*,struct rtw_backup_info*) ; 
 int /*<<< orphan*/  rtw8822c_dac_bb_setting (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_adc (struct rtw_dev*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_backup (struct rtw_dev*) ; 
 scalar_t__ rtw8822c_dac_cal_restore (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_step1 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_step2 (struct rtw_dev*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_step3 (struct rtw_dev*,int /*<<< orphan*/ ,int,int,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_step4 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw8822c_dac_restore_reg (struct rtw_dev*,struct rtw_backup_info*,struct rtw_backup_info*) ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int,int) ; 

__attribute__((used)) static void rtw8822c_rf_dac_cal(struct rtw_dev *rtwdev)
{
	struct rtw_backup_info backup_rf[DACK_RF_8822C * DACK_PATH_8822C];
	struct rtw_backup_info backup[DACK_REG_8822C];
	u32 ic = 0, qc = 0, i;
	u32 i_a = 0x0, q_a = 0x0, i_b = 0x0, q_b = 0x0;
	u32 ic_a = 0x0, qc_a = 0x0, ic_b = 0x0, qc_b = 0x0;
	u32 adc_ic_a = 0x0, adc_qc_a = 0x0, adc_ic_b = 0x0, adc_qc_b = 0x0;

	if (rtw8822c_dac_cal_restore(rtwdev))
		return;

	/* not able to restore, do it */

	rtw8822c_dac_backup_reg(rtwdev, backup, backup_rf);

	rtw8822c_dac_bb_setting(rtwdev);

	/* path-A */
	rtw8822c_dac_cal_adc(rtwdev, RF_PATH_A, &adc_ic_a, &adc_qc_a);
	for (i = 0; i < 10; i++) {
		rtw8822c_dac_cal_step1(rtwdev, RF_PATH_A);
		rtw8822c_dac_cal_step2(rtwdev, RF_PATH_A, &ic, &qc);
		ic_a = ic;
		qc_a = qc;

		rtw8822c_dac_cal_step3(rtwdev, RF_PATH_A, adc_ic_a, adc_qc_a,
				       &ic, &qc, &i_a, &q_a);

		if (ic < 5 && qc < 5)
			break;
	}
	rtw8822c_dac_cal_step4(rtwdev, RF_PATH_A);

	/* path-B */
	rtw8822c_dac_cal_adc(rtwdev, RF_PATH_B, &adc_ic_b, &adc_qc_b);
	for (i = 0; i < 10; i++) {
		rtw8822c_dac_cal_step1(rtwdev, RF_PATH_B);
		rtw8822c_dac_cal_step2(rtwdev, RF_PATH_B, &ic, &qc);
		ic_b = ic;
		qc_b = qc;

		rtw8822c_dac_cal_step3(rtwdev, RF_PATH_B, adc_ic_b, adc_qc_b,
				       &ic, &qc, &i_b, &q_b);

		if (ic < 5 && qc < 5)
			break;
	}
	rtw8822c_dac_cal_step4(rtwdev, RF_PATH_B);

	rtw_write32(rtwdev, 0x1b00, 0x00000008);
	rtw_write32_mask(rtwdev, 0x4130, BIT(30), 0x1);
	rtw_write8(rtwdev, 0x1bcc, 0x0);
	rtw_write32(rtwdev, 0x1b00, 0x0000000a);
	rtw_write8(rtwdev, 0x1bcc, 0x0);

	rtw8822c_dac_restore_reg(rtwdev, backup, backup_rf);

	/* backup results to restore, saving a lot of time */
	rtw8822c_dac_cal_backup(rtwdev);

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] path A: ic=0x%x, qc=0x%x\n", ic_a, qc_a);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] path B: ic=0x%x, qc=0x%x\n", ic_b, qc_b);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] path A: i=0x%x, q=0x%x\n", i_a, q_a);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] path B: i=0x%x, q=0x%x\n", i_b, q_b);
}