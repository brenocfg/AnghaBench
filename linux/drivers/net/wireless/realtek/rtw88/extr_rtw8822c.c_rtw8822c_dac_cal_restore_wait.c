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
typedef  scalar_t__ u32 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int rtw_read32_mask (struct rtw_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,scalar_t__,int,int) ; 

__attribute__((used)) static bool rtw8822c_dac_cal_restore_wait(struct rtw_dev *rtwdev,
					  u32 target_addr, u32 toggle_addr)
{
	u32 cnt = 0;

	do {
		rtw_write32_mask(rtwdev, toggle_addr, BIT(26) | BIT(25), 0x0);
		rtw_write32_mask(rtwdev, toggle_addr, BIT(26) | BIT(25), 0x2);

		if (rtw_read32_mask(rtwdev, target_addr, 0xf) == 0x6)
			return true;

	} while (cnt++ < 100);

	return false;
}