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
typedef  int u32 ;
struct rtw_dm_info {int* dack_adck; } ;
struct rtw_dev {struct rtw_dm_info dm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  RFREG_MASK ; 
#define  RF_PATH_A 129 
#define  RF_PATH_B 128 
 int /*<<< orphan*/  RTW_DBG_RFK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_rf_mode (struct rtw_dev*,int*,int*) ; 
 int rtw8822c_get_path_write_addr (int) ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write_rf (struct rtw_dev*,int const,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822c_dac_cal_adc(struct rtw_dev *rtwdev,
				 u8 path, u32 *adc_ic, u32 *adc_qc)
{
	struct rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 ic = 0, qc = 0, temp = 0;
	u32 base_addr;
	u32 path_sel;
	int i;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] ADCK path(%d)\n", path);

	base_addr = rtw8822c_get_path_write_addr(path);
	switch (path) {
	case RF_PATH_A:
		path_sel = 0xa0000;
		break;
	case RF_PATH_B:
		path_sel = 0x80000;
		break;
	default:
		WARN_ON(1);
		return;
	}

	/* ADCK step1 */
	rtw_write32_mask(rtwdev, base_addr + 0x30, BIT(30), 0x0);
	if (path == RF_PATH_B)
		rtw_write32(rtwdev, base_addr + 0x30, 0x30db8041);
	rtw_write32(rtwdev, base_addr + 0x60, 0xf0040ff0);
	rtw_write32(rtwdev, base_addr + 0x0c, 0xdff00220);
	rtw_write32(rtwdev, base_addr + 0x10, 0x02dd08c4);
	rtw_write32(rtwdev, base_addr + 0x0c, 0x10000260);
	rtw_write_rf(rtwdev, RF_PATH_A, 0x0, RFREG_MASK, 0x10000);
	rtw_write_rf(rtwdev, RF_PATH_B, 0x0, RFREG_MASK, 0x10000);
	for (i = 0; i < 10; i++) {
		rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] ADCK count=%d\n", i);
		rtw_write32(rtwdev, 0x1c3c, path_sel + 0x8003);
		rtw_write32(rtwdev, 0x1c24, 0x00010002);
		rtw8822c_dac_cal_rf_mode(rtwdev, &ic, &qc);
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[DACK] before: i=0x%x, q=0x%x\n", ic, qc);

		/* compensation value */
		if (ic != 0x0) {
			ic = 0x400 - ic;
			*adc_ic = ic;
		}
		if (qc != 0x0) {
			qc = 0x400 - qc;
			*adc_qc = qc;
		}
		temp = (ic & 0x3ff) | ((qc & 0x3ff) << 10);
		rtw_write32(rtwdev, base_addr + 0x68, temp);
		dm_info->dack_adck[path] = temp;
		rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] ADCK 0x%08x=0x08%x\n",
			base_addr + 0x68, temp);
		/* check ADC DC offset */
		rtw_write32(rtwdev, 0x1c3c, path_sel + 0x8103);
		rtw8822c_dac_cal_rf_mode(rtwdev, &ic, &qc);
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[DACK] after:  i=0x%08x, q=0x%08x\n", ic, qc);
		if (ic >= 0x200)
			ic = 0x400 - ic;
		if (qc >= 0x200)
			qc = 0x400 - qc;
		if (ic < 5 && qc < 5)
			break;
	}

	/* ADCK step2 */
	rtw_write32(rtwdev, 0x1c3c, 0x00000003);
	rtw_write32(rtwdev, base_addr + 0x0c, 0x10000260);
	rtw_write32(rtwdev, base_addr + 0x10, 0x02d508c4);

	/* release pull low switch on IQ path */
	rtw_write_rf(rtwdev, path, 0x8f, BIT(13), 0x1);
}