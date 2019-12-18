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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_DBG_RFK ; 
 int /*<<< orphan*/  check_hw_ready (struct rtw_dev*,int,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rtw8822c_dac_cal_rf_mode (struct rtw_dev*,int*,int*) ; 
 int rtw8822c_get_path_read_addr (int /*<<< orphan*/ ) ; 
 int rtw8822c_get_path_write_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int,int) ; 

__attribute__((used)) static void rtw8822c_dac_cal_step3(struct rtw_dev *rtwdev, u8 path,
				   u32 adc_ic, u32 adc_qc,
				   u32 *ic_in, u32 *qc_in,
				   u32 *i_out, u32 *q_out)
{
	u32 base_addr;
	u32 read_addr;
	u32 ic, qc;
	u32 temp;

	base_addr = rtw8822c_get_path_write_addr(path);
	read_addr = rtw8822c_get_path_read_addr(path);
	ic = *ic_in;
	qc = *qc_in;

	rtw_write32(rtwdev, base_addr + 0x0c, 0xdff00220);
	rtw_write32(rtwdev, base_addr + 0x10, 0x02d508c5);
	rtw_write32(rtwdev, 0x9b4, 0xdb66db00);
	rtw_write32(rtwdev, base_addr + 0xb0, 0x0a11fb88);
	rtw_write32(rtwdev, base_addr + 0xbc, 0xc008ff81);
	rtw_write32(rtwdev, base_addr + 0xc0, 0x0003d208);
	rtw_write32_mask(rtwdev, base_addr + 0xbc, 0xf0000000, ic & 0xf);
	rtw_write32_mask(rtwdev, base_addr + 0xc0, 0xf, (ic & 0xf0) >> 4);
	rtw_write32(rtwdev, base_addr + 0xcc, 0x0a11fb88);
	rtw_write32(rtwdev, base_addr + 0xd8, 0xe008ff81);
	rtw_write32(rtwdev, base_addr + 0xdc, 0x0003d208);
	rtw_write32_mask(rtwdev, base_addr + 0xd8, 0xf0000000, qc & 0xf);
	rtw_write32_mask(rtwdev, base_addr + 0xdc, 0xf, (qc & 0xf0) >> 4);
	rtw_write32(rtwdev, base_addr + 0xb8, 0x60000000);
	mdelay(2);
	rtw_write32_mask(rtwdev, base_addr + 0xbc, 0xe, 0x6);
	mdelay(2);
	rtw_write32(rtwdev, base_addr + 0xb0, 0x0a11fb89);
	rtw_write32(rtwdev, base_addr + 0xcc, 0x0a11fb89);
	mdelay(1);
	rtw_write32(rtwdev, base_addr + 0xb8, 0x62000000);
	rtw_write32(rtwdev, base_addr + 0xd4, 0x62000000);
	mdelay(20);
	if (!check_hw_ready(rtwdev, read_addr + 0x24, 0x07f80000, ic) ||
	    !check_hw_ready(rtwdev, read_addr + 0x50, 0x07f80000, qc))
		rtw_err(rtwdev, "failed to write IQ vector to hardware\n");
	rtw_write32(rtwdev, base_addr + 0xb8, 0x02000000);
	mdelay(1);
	rtw_write32_mask(rtwdev, base_addr + 0xbc, 0xe, 0x3);
	rtw_write32(rtwdev, 0x9b4, 0xdb6db600);

	/* check DAC DC offset */
	temp = ((adc_ic + 0x10) & 0x3ff) | (((adc_qc + 0x10) & 0x3ff) << 10);
	rtw_write32(rtwdev, base_addr + 0x68, temp);
	rtw_write32(rtwdev, base_addr + 0x10, 0x02d508c5);
	rtw_write32(rtwdev, base_addr + 0x60, 0xf0000000);
	rtw8822c_dac_cal_rf_mode(rtwdev, &ic, &qc);
	if (ic >= 0x10)
		ic = ic - 0x10;
	else
		ic = 0x400 - (0x10 - ic);

	if (qc >= 0x10)
		qc = qc - 0x10;
	else
		qc = 0x400 - (0x10 - qc);

	*i_out = ic;
	*q_out = qc;

	if (ic >= 0x200)
		ic = 0x400 - ic;
	if (qc >= 0x200)
		qc = 0x400 - qc;

	*ic_in = ic;
	*qc_in = qc;

	rtw_dbg(rtwdev, RTW_DBG_RFK,
		"[DACK] after  DACK i=0x%x, q=0x%x\n", *i_out, *q_out);
}