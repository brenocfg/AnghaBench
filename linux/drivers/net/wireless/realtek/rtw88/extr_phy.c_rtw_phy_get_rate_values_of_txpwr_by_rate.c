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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int DESC_RATE11M ; 
 int DESC_RATE12M ; 
 int DESC_RATE18M ; 
 int DESC_RATE1M ; 
 int DESC_RATE24M ; 
 int DESC_RATE2M ; 
 int DESC_RATE36M ; 
 int DESC_RATE48M ; 
 int DESC_RATE54M ; 
 int DESC_RATE5_5M ; 
 int DESC_RATE6M ; 
 int DESC_RATE9M ; 
 int DESC_RATEMCS0 ; 
 int DESC_RATEMCS1 ; 
 int DESC_RATEMCS10 ; 
 int DESC_RATEMCS11 ; 
 int DESC_RATEMCS12 ; 
 int DESC_RATEMCS13 ; 
 int DESC_RATEMCS14 ; 
 int DESC_RATEMCS15 ; 
 int DESC_RATEMCS16 ; 
 int DESC_RATEMCS17 ; 
 int DESC_RATEMCS18 ; 
 int DESC_RATEMCS19 ; 
 int DESC_RATEMCS2 ; 
 int DESC_RATEMCS20 ; 
 int DESC_RATEMCS21 ; 
 int DESC_RATEMCS22 ; 
 int DESC_RATEMCS23 ; 
 int DESC_RATEMCS3 ; 
 int DESC_RATEMCS4 ; 
 int DESC_RATEMCS5 ; 
 int DESC_RATEMCS6 ; 
 int DESC_RATEMCS7 ; 
 int DESC_RATEMCS8 ; 
 int DESC_RATEMCS9 ; 
 int DESC_RATEVHT1SS_MCS0 ; 
 int DESC_RATEVHT1SS_MCS1 ; 
 int DESC_RATEVHT1SS_MCS2 ; 
 int DESC_RATEVHT1SS_MCS3 ; 
 int DESC_RATEVHT1SS_MCS4 ; 
 int DESC_RATEVHT1SS_MCS5 ; 
 int DESC_RATEVHT1SS_MCS6 ; 
 int DESC_RATEVHT1SS_MCS7 ; 
 int DESC_RATEVHT1SS_MCS8 ; 
 int DESC_RATEVHT1SS_MCS9 ; 
 int DESC_RATEVHT2SS_MCS0 ; 
 int DESC_RATEVHT2SS_MCS1 ; 
 int DESC_RATEVHT2SS_MCS2 ; 
 int DESC_RATEVHT2SS_MCS3 ; 
 int DESC_RATEVHT2SS_MCS4 ; 
 int DESC_RATEVHT2SS_MCS5 ; 
 int DESC_RATEVHT2SS_MCS6 ; 
 int DESC_RATEVHT2SS_MCS7 ; 
 int DESC_RATEVHT2SS_MCS8 ; 
 int DESC_RATEVHT2SS_MCS9 ; 
 int DESC_RATEVHT3SS_MCS0 ; 
 int DESC_RATEVHT3SS_MCS1 ; 
 int DESC_RATEVHT3SS_MCS2 ; 
 int DESC_RATEVHT3SS_MCS3 ; 
 int DESC_RATEVHT3SS_MCS4 ; 
 int DESC_RATEVHT3SS_MCS5 ; 
 int DESC_RATEVHT3SS_MCS6 ; 
 int DESC_RATEVHT3SS_MCS7 ; 
 int DESC_RATEVHT3SS_MCS8 ; 
 int DESC_RATEVHT3SS_MCS9 ; 
 int bcd_to_dec_pwr_by_rate (int,int) ; 
 int /*<<< orphan*/  rtw_warn (struct rtw_dev*,char*,int) ; 
 int tbl_to_dec_pwr_by_rate (struct rtw_dev*,int,int) ; 

__attribute__((used)) static void
rtw_phy_get_rate_values_of_txpwr_by_rate(struct rtw_dev *rtwdev,
					 u32 addr, u32 mask, u32 val, u8 *rate,
					 u8 *pwr_by_rate, u8 *rate_num)
{
	int i;

	switch (addr) {
	case 0xE00:
	case 0x830:
		rate[0] = DESC_RATE6M;
		rate[1] = DESC_RATE9M;
		rate[2] = DESC_RATE12M;
		rate[3] = DESC_RATE18M;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xE04:
	case 0x834:
		rate[0] = DESC_RATE24M;
		rate[1] = DESC_RATE36M;
		rate[2] = DESC_RATE48M;
		rate[3] = DESC_RATE54M;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xE08:
		rate[0] = DESC_RATE1M;
		pwr_by_rate[0] = bcd_to_dec_pwr_by_rate(val, 1);
		*rate_num = 1;
		break;
	case 0x86C:
		if (mask == 0xffffff00) {
			rate[0] = DESC_RATE2M;
			rate[1] = DESC_RATE5_5M;
			rate[2] = DESC_RATE11M;
			for (i = 1; i < 4; ++i)
				pwr_by_rate[i - 1] =
					tbl_to_dec_pwr_by_rate(rtwdev, val, i);
			*rate_num = 3;
		} else if (mask == 0x000000ff) {
			rate[0] = DESC_RATE11M;
			pwr_by_rate[0] = bcd_to_dec_pwr_by_rate(val, 0);
			*rate_num = 1;
		}
		break;
	case 0xE10:
	case 0x83C:
		rate[0] = DESC_RATEMCS0;
		rate[1] = DESC_RATEMCS1;
		rate[2] = DESC_RATEMCS2;
		rate[3] = DESC_RATEMCS3;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xE14:
	case 0x848:
		rate[0] = DESC_RATEMCS4;
		rate[1] = DESC_RATEMCS5;
		rate[2] = DESC_RATEMCS6;
		rate[3] = DESC_RATEMCS7;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xE18:
	case 0x84C:
		rate[0] = DESC_RATEMCS8;
		rate[1] = DESC_RATEMCS9;
		rate[2] = DESC_RATEMCS10;
		rate[3] = DESC_RATEMCS11;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xE1C:
	case 0x868:
		rate[0] = DESC_RATEMCS12;
		rate[1] = DESC_RATEMCS13;
		rate[2] = DESC_RATEMCS14;
		rate[3] = DESC_RATEMCS15;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0x838:
		rate[0] = DESC_RATE1M;
		rate[1] = DESC_RATE2M;
		rate[2] = DESC_RATE5_5M;
		for (i = 1; i < 4; ++i)
			pwr_by_rate[i - 1] = tbl_to_dec_pwr_by_rate(rtwdev,
								    val, i);
		*rate_num = 3;
		break;
	case 0xC20:
	case 0xE20:
	case 0x1820:
	case 0x1A20:
		rate[0] = DESC_RATE1M;
		rate[1] = DESC_RATE2M;
		rate[2] = DESC_RATE5_5M;
		rate[3] = DESC_RATE11M;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xC24:
	case 0xE24:
	case 0x1824:
	case 0x1A24:
		rate[0] = DESC_RATE6M;
		rate[1] = DESC_RATE9M;
		rate[2] = DESC_RATE12M;
		rate[3] = DESC_RATE18M;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xC28:
	case 0xE28:
	case 0x1828:
	case 0x1A28:
		rate[0] = DESC_RATE24M;
		rate[1] = DESC_RATE36M;
		rate[2] = DESC_RATE48M;
		rate[3] = DESC_RATE54M;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xC2C:
	case 0xE2C:
	case 0x182C:
	case 0x1A2C:
		rate[0] = DESC_RATEMCS0;
		rate[1] = DESC_RATEMCS1;
		rate[2] = DESC_RATEMCS2;
		rate[3] = DESC_RATEMCS3;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xC30:
	case 0xE30:
	case 0x1830:
	case 0x1A30:
		rate[0] = DESC_RATEMCS4;
		rate[1] = DESC_RATEMCS5;
		rate[2] = DESC_RATEMCS6;
		rate[3] = DESC_RATEMCS7;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xC34:
	case 0xE34:
	case 0x1834:
	case 0x1A34:
		rate[0] = DESC_RATEMCS8;
		rate[1] = DESC_RATEMCS9;
		rate[2] = DESC_RATEMCS10;
		rate[3] = DESC_RATEMCS11;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xC38:
	case 0xE38:
	case 0x1838:
	case 0x1A38:
		rate[0] = DESC_RATEMCS12;
		rate[1] = DESC_RATEMCS13;
		rate[2] = DESC_RATEMCS14;
		rate[3] = DESC_RATEMCS15;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xC3C:
	case 0xE3C:
	case 0x183C:
	case 0x1A3C:
		rate[0] = DESC_RATEVHT1SS_MCS0;
		rate[1] = DESC_RATEVHT1SS_MCS1;
		rate[2] = DESC_RATEVHT1SS_MCS2;
		rate[3] = DESC_RATEVHT1SS_MCS3;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xC40:
	case 0xE40:
	case 0x1840:
	case 0x1A40:
		rate[0] = DESC_RATEVHT1SS_MCS4;
		rate[1] = DESC_RATEVHT1SS_MCS5;
		rate[2] = DESC_RATEVHT1SS_MCS6;
		rate[3] = DESC_RATEVHT1SS_MCS7;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xC44:
	case 0xE44:
	case 0x1844:
	case 0x1A44:
		rate[0] = DESC_RATEVHT1SS_MCS8;
		rate[1] = DESC_RATEVHT1SS_MCS9;
		rate[2] = DESC_RATEVHT2SS_MCS0;
		rate[3] = DESC_RATEVHT2SS_MCS1;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xC48:
	case 0xE48:
	case 0x1848:
	case 0x1A48:
		rate[0] = DESC_RATEVHT2SS_MCS2;
		rate[1] = DESC_RATEVHT2SS_MCS3;
		rate[2] = DESC_RATEVHT2SS_MCS4;
		rate[3] = DESC_RATEVHT2SS_MCS5;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xC4C:
	case 0xE4C:
	case 0x184C:
	case 0x1A4C:
		rate[0] = DESC_RATEVHT2SS_MCS6;
		rate[1] = DESC_RATEVHT2SS_MCS7;
		rate[2] = DESC_RATEVHT2SS_MCS8;
		rate[3] = DESC_RATEVHT2SS_MCS9;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xCD8:
	case 0xED8:
	case 0x18D8:
	case 0x1AD8:
		rate[0] = DESC_RATEMCS16;
		rate[1] = DESC_RATEMCS17;
		rate[2] = DESC_RATEMCS18;
		rate[3] = DESC_RATEMCS19;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xCDC:
	case 0xEDC:
	case 0x18DC:
	case 0x1ADC:
		rate[0] = DESC_RATEMCS20;
		rate[1] = DESC_RATEMCS21;
		rate[2] = DESC_RATEMCS22;
		rate[3] = DESC_RATEMCS23;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xCE0:
	case 0xEE0:
	case 0x18E0:
	case 0x1AE0:
		rate[0] = DESC_RATEVHT3SS_MCS0;
		rate[1] = DESC_RATEVHT3SS_MCS1;
		rate[2] = DESC_RATEVHT3SS_MCS2;
		rate[3] = DESC_RATEVHT3SS_MCS3;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xCE4:
	case 0xEE4:
	case 0x18E4:
	case 0x1AE4:
		rate[0] = DESC_RATEVHT3SS_MCS4;
		rate[1] = DESC_RATEVHT3SS_MCS5;
		rate[2] = DESC_RATEVHT3SS_MCS6;
		rate[3] = DESC_RATEVHT3SS_MCS7;
		for (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		break;
	case 0xCE8:
	case 0xEE8:
	case 0x18E8:
	case 0x1AE8:
		rate[0] = DESC_RATEVHT3SS_MCS8;
		rate[1] = DESC_RATEVHT3SS_MCS9;
		for (i = 0; i < 2; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 2;
		break;
	default:
		rtw_warn(rtwdev, "invalid tx power index addr 0x%08x\n", addr);
		break;
	}
}