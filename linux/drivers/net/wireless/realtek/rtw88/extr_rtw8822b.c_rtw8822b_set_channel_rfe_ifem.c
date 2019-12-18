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
struct rtw_hal {scalar_t__ antenna_rx; scalar_t__ antenna_tx; } ;
struct rtw_dev {struct rtw_hal hal; } ;

/* Variables and functions */
 scalar_t__ BB_PATH_AB ; 
 int BIT (int) ; 
 int MASKBYTE1 ; 
 int MASKLWORD ; 
 int /*<<< orphan*/  REG_RFEINV ; 
 int /*<<< orphan*/  REG_RFESEL0 ; 
 int /*<<< orphan*/  REG_RFESEL8 ; 
 int /*<<< orphan*/  REG_TRSW ; 
 int /*<<< orphan*/  rtw_write32s_mask (struct rtw_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtw8822b_set_channel_rfe_ifem(struct rtw_dev *rtwdev, u8 channel)
{
	struct rtw_hal *hal = &rtwdev->hal;
	bool is_channel_2g = (channel <= 14) ? true : false;

	if (is_channel_2g) {
		/* signal source */
		rtw_write32s_mask(rtwdev, REG_RFESEL0, 0xffffff, 0x745774);
		rtw_write32s_mask(rtwdev, REG_RFESEL8, MASKBYTE1, 0x57);
	} else {
		/* signal source */
		rtw_write32s_mask(rtwdev, REG_RFESEL0, 0xffffff, 0x477547);
		rtw_write32s_mask(rtwdev, REG_RFESEL8, MASKBYTE1, 0x75);
	}

	rtw_write32s_mask(rtwdev, REG_RFEINV, BIT(11) | BIT(10) | 0x3f, 0x0);

	if (is_channel_2g) {
		if (hal->antenna_rx == BB_PATH_AB ||
		    hal->antenna_tx == BB_PATH_AB) {
			/* 2TX or 2RX */
			rtw_write32s_mask(rtwdev, REG_TRSW, MASKLWORD, 0xa501);
		} else if (hal->antenna_rx == hal->antenna_tx) {
			/* TXA+RXA or TXB+RXB */
			rtw_write32s_mask(rtwdev, REG_TRSW, MASKLWORD, 0xa500);
		} else {
			/* TXB+RXA or TXA+RXB */
			rtw_write32s_mask(rtwdev, REG_TRSW, MASKLWORD, 0xa005);
		}
	} else {
		rtw_write32s_mask(rtwdev, REG_TRSW, MASKLWORD, 0xa5a5);
	}
}