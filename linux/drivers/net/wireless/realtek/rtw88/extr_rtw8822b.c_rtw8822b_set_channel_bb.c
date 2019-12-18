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
struct rtw_efuse {int rfe_option; } ;
struct rtw_dev {struct rtw_efuse efuse; } ;

/* Variables and functions */
 int const BIT (int) ; 
 int const MASKDWORD ; 
 int const MASKLWORD ; 
 int REG_ACGG2TBL ; 
 int REG_ADC160 ; 
 int REG_ADC40 ; 
 int REG_ADCCLK ; 
 int REG_CCK_CHECK ; 
 int REG_CLKTRK ; 
 int REG_ENTXCCK ; 
 int REG_L1PKWT ; 
 int REG_RFEINV ; 
 int REG_RXCCAMSK ; 
 int REG_RXPSEL ; 
 int /*<<< orphan*/  REG_RXSB ; 
 int REG_TXSF2 ; 
 int REG_TXSF6 ; 
#define  RTW_CHANNEL_WIDTH_10 132 
#define  RTW_CHANNEL_WIDTH_20 131 
#define  RTW_CHANNEL_WIDTH_40 130 
#define  RTW_CHANNEL_WIDTH_5 129 
#define  RTW_CHANNEL_WIDTH_80 128 
 int rtw_read32_mask (struct rtw_dev*,int,int const) ; 
 int /*<<< orphan*/  rtw_write32_clr (struct rtw_dev*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int const,int) ; 
 int /*<<< orphan*/  rtw_write32_set (struct rtw_dev*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void rtw8822b_set_channel_bb(struct rtw_dev *rtwdev, u8 channel, u8 bw,
				    u8 primary_ch_idx)
{
	struct rtw_efuse *efuse = &rtwdev->efuse;
	u8 rfe_option = efuse->rfe_option;
	u32 val32;

	if (channel <= 14) {
		rtw_write32_mask(rtwdev, REG_RXPSEL, BIT(28), 0x1);
		rtw_write32_mask(rtwdev, REG_CCK_CHECK, BIT(7), 0x0);
		rtw_write32_mask(rtwdev, REG_ENTXCCK, BIT(18), 0x0);
		rtw_write32_mask(rtwdev, REG_RXCCAMSK, 0x0000FC00, 15);

		rtw_write32_mask(rtwdev, REG_ACGG2TBL, 0x1f, 0x0);
		rtw_write32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x96a);
		if (channel == 14) {
			rtw_write32_mask(rtwdev, REG_TXSF2, MASKDWORD, 0x00006577);
			rtw_write32_mask(rtwdev, REG_TXSF6, MASKLWORD, 0x0000);
		} else {
			rtw_write32_mask(rtwdev, REG_TXSF2, MASKDWORD, 0x384f6577);
			rtw_write32_mask(rtwdev, REG_TXSF6, MASKLWORD, 0x1525);
		}

		rtw_write32_mask(rtwdev, REG_RFEINV, 0x300, 0x2);
	} else if (channel > 35) {
		rtw_write32_mask(rtwdev, REG_ENTXCCK, BIT(18), 0x1);
		rtw_write32_mask(rtwdev, REG_CCK_CHECK, BIT(7), 0x1);
		rtw_write32_mask(rtwdev, REG_RXPSEL, BIT(28), 0x0);
		rtw_write32_mask(rtwdev, REG_RXCCAMSK, 0x0000FC00, 34);

		if (channel >= 36 && channel <= 64)
			rtw_write32_mask(rtwdev, REG_ACGG2TBL, 0x1f, 0x1);
		else if (channel >= 100 && channel <= 144)
			rtw_write32_mask(rtwdev, REG_ACGG2TBL, 0x1f, 0x2);
		else if (channel >= 149)
			rtw_write32_mask(rtwdev, REG_ACGG2TBL, 0x1f, 0x3);

		if (channel >= 36 && channel <= 48)
			rtw_write32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x494);
		else if (channel >= 52 && channel <= 64)
			rtw_write32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x453);
		else if (channel >= 100 && channel <= 116)
			rtw_write32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x452);
		else if (channel >= 118 && channel <= 177)
			rtw_write32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x412);

		rtw_write32_mask(rtwdev, 0xcbc, 0x300, 0x1);
	}

	switch (bw) {
	case RTW_CHANNEL_WIDTH_20:
	default:
		val32 = rtw_read32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xFFCFFC00;
		val32 |= (RTW_CHANNEL_WIDTH_20);
		rtw_write32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_write32_mask(rtwdev, REG_ADC160, BIT(30), 0x1);
		break;
	case RTW_CHANNEL_WIDTH_40:
		if (primary_ch_idx == 1)
			rtw_write32_set(rtwdev, REG_RXSB, BIT(4));
		else
			rtw_write32_clr(rtwdev, REG_RXSB, BIT(4));

		val32 = rtw_read32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xFF3FF300;
		val32 |= (((primary_ch_idx & 0xf) << 2) | RTW_CHANNEL_WIDTH_40);
		rtw_write32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_write32_mask(rtwdev, REG_ADC160, BIT(30), 0x1);
		break;
	case RTW_CHANNEL_WIDTH_80:
		val32 = rtw_read32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xFCEFCF00;
		val32 |= (((primary_ch_idx & 0xf) << 2) | RTW_CHANNEL_WIDTH_80);
		rtw_write32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_write32_mask(rtwdev, REG_ADC160, BIT(30), 0x1);

		if (rfe_option == 2) {
			rtw_write32_mask(rtwdev, REG_L1PKWT, 0x0000f000, 0x6);
			rtw_write32_mask(rtwdev, REG_ADC40, BIT(10), 0x1);
		}
		break;
	case RTW_CHANNEL_WIDTH_5:
		val32 = rtw_read32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xEFEEFE00;
		val32 |= ((BIT(6) | RTW_CHANNEL_WIDTH_20));
		rtw_write32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_write32_mask(rtwdev, REG_ADC160, BIT(30), 0x0);
		rtw_write32_mask(rtwdev, REG_ADC40, BIT(31), 0x1);
		break;
	case RTW_CHANNEL_WIDTH_10:
		val32 = rtw_read32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xEFFEFF00;
		val32 |= ((BIT(7) | RTW_CHANNEL_WIDTH_20));
		rtw_write32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_write32_mask(rtwdev, REG_ADC160, BIT(30), 0x0);
		rtw_write32_mask(rtwdev, REG_ADC40, BIT(31), 0x1);
		break;
	}
}