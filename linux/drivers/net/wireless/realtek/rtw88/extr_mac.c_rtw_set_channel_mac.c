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
 int BIT_CHECK_CCK_EN ; 
 int BIT_MAC_CLK_SEL ; 
 int BIT_RFMOD ; 
 int BIT_RFMOD_40M ; 
 int BIT_RFMOD_80M ; 
 int BIT_SHIFT_MAC_CLK_SEL ; 
 int BIT_TXSC_20M (int) ; 
 int BIT_TXSC_40M (int) ; 
 int MAC_CLK_HW_DEF_80M ; 
 int MAC_CLK_SPEED ; 
 int /*<<< orphan*/  REG_AFE_CTRL1 ; 
 int /*<<< orphan*/  REG_CCK_CHECK ; 
 int /*<<< orphan*/  REG_DATA_SC ; 
 int /*<<< orphan*/  REG_USTIME_EDCA ; 
 int /*<<< orphan*/  REG_USTIME_TSF ; 
 int /*<<< orphan*/  REG_WMAC_TRXPTCL_CTL ; 
#define  RTW_CHANNEL_WIDTH_20 130 
#define  RTW_CHANNEL_WIDTH_40 129 
#define  RTW_CHANNEL_WIDTH_80 128 
 int rtw_read32 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int rtw_read8 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

void rtw_set_channel_mac(struct rtw_dev *rtwdev, u8 channel, u8 bw,
			 u8 primary_ch_idx)
{
	u8 txsc40 = 0, txsc20 = 0;
	u32 value32;
	u8 value8;

	txsc20 = primary_ch_idx;
	if (txsc20 == 1 || txsc20 == 3)
		txsc40 = 9;
	else
		txsc40 = 10;
	rtw_write8(rtwdev, REG_DATA_SC,
		   BIT_TXSC_20M(txsc20) | BIT_TXSC_40M(txsc40));

	value32 = rtw_read32(rtwdev, REG_WMAC_TRXPTCL_CTL);
	value32 &= ~BIT_RFMOD;
	switch (bw) {
	case RTW_CHANNEL_WIDTH_80:
		value32 |= BIT_RFMOD_80M;
		break;
	case RTW_CHANNEL_WIDTH_40:
		value32 |= BIT_RFMOD_40M;
		break;
	case RTW_CHANNEL_WIDTH_20:
	default:
		break;
	}
	rtw_write32(rtwdev, REG_WMAC_TRXPTCL_CTL, value32);

	value32 = rtw_read32(rtwdev, REG_AFE_CTRL1) & ~(BIT_MAC_CLK_SEL);
	value32 |= (MAC_CLK_HW_DEF_80M << BIT_SHIFT_MAC_CLK_SEL);
	rtw_write32(rtwdev, REG_AFE_CTRL1, value32);

	rtw_write8(rtwdev, REG_USTIME_TSF, MAC_CLK_SPEED);
	rtw_write8(rtwdev, REG_USTIME_EDCA, MAC_CLK_SPEED);

	value8 = rtw_read8(rtwdev, REG_CCK_CHECK);
	value8 = value8 & ~BIT_CHECK_CCK_EN;
	if (channel > 35)
		value8 |= BIT_CHECK_CCK_EN;
	rtw_write8(rtwdev, REG_CCK_CHECK, value8);
}