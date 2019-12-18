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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  RFREG_MASK ; 
 int /*<<< orphan*/  RF_PATH_A ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rtw_read_rf (struct rtw_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write_rf (struct rtw_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822c_rf_x2_check(struct rtw_dev *rtwdev)
{
	u8 x2k_busy;

	mdelay(1);
	x2k_busy = rtw_read_rf(rtwdev, RF_PATH_A, 0xb8, BIT(15));
	if (x2k_busy == 1) {
		rtw_write_rf(rtwdev, RF_PATH_A, 0xb8, RFREG_MASK, 0xC4440);
		rtw_write_rf(rtwdev, RF_PATH_A, 0xba, RFREG_MASK, 0x6840D);
		rtw_write_rf(rtwdev, RF_PATH_A, 0xb8, RFREG_MASK, 0x80440);
		mdelay(1);
	}
}