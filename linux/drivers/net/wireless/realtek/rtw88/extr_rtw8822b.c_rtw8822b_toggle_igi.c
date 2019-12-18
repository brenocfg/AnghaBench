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
struct rtw_hal {int antenna_rx; } ;
struct rtw_dev {struct rtw_hal hal; } ;

/* Variables and functions */
 int MASKBYTE0 ; 
 int /*<<< orphan*/  REG_RXIGI_A ; 
 int /*<<< orphan*/  REG_RXIGI_B ; 
 int /*<<< orphan*/  REG_RXPSEL ; 
 int rtw_read32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtw8822b_toggle_igi(struct rtw_dev *rtwdev)
{
	struct rtw_hal *hal = &rtwdev->hal;
	u32 igi;

	igi = rtw_read32_mask(rtwdev, REG_RXIGI_A, 0x7f);
	rtw_write32_mask(rtwdev, REG_RXIGI_A, 0x7f, igi - 2);
	rtw_write32_mask(rtwdev, REG_RXIGI_A, 0x7f, igi);
	rtw_write32_mask(rtwdev, REG_RXIGI_B, 0x7f, igi - 2);
	rtw_write32_mask(rtwdev, REG_RXIGI_B, 0x7f, igi);

	rtw_write32_mask(rtwdev, REG_RXPSEL, MASKBYTE0, 0x0);
	rtw_write32_mask(rtwdev, REG_RXPSEL, MASKBYTE0,
			 hal->antenna_rx | (hal->antenna_rx << 4));
}