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
 int DACK_SN_8822C ; 
 scalar_t__ rtw8822c_dac_iq_check (struct rtw_dev*,int) ; 
 int rtw_read32_mask (struct rtw_dev*,int,int) ; 

__attribute__((used)) static void rtw8822c_dac_cal_iq_sample(struct rtw_dev *rtwdev, u32 *iv, u32 *qv)
{
	u32 temp;
	int i = 0, cnt = 0;

	while (i < DACK_SN_8822C && cnt < 10000) {
		cnt++;
		temp = rtw_read32_mask(rtwdev, 0x2dbc, 0x3fffff);
		iv[i] = (temp & 0x3ff000) >> 12;
		qv[i] = temp & 0x3ff;

		if (rtw8822c_dac_iq_check(rtwdev, iv[i]) &&
		    rtw8822c_dac_iq_check(rtwdev, qv[i]))
			i++;
	}
}