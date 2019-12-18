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
typedef  scalar_t__ u32 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ REG_BT_COEX_TABLE_H ; 
 int /*<<< orphan*/  rtw_write8_mask (struct rtw_dev*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw_coex_set_wl_pri_mask(struct rtw_dev *rtwdev, u8 bitmap,
				     u8 data)
{
	u32 addr;

	addr = REG_BT_COEX_TABLE_H + (bitmap / 8);
	bitmap = bitmap % 8;

	rtw_write8_mask(rtwdev, addr, BIT(bitmap), data);
}