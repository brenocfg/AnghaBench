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
typedef  scalar_t__ u32 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ rtw8822c_get_path_write_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,scalar_t__,int,int) ; 

__attribute__((used)) static void rtw8822c_dac_cal_step4(struct rtw_dev *rtwdev, u8 path)
{
	u32 base_addr = rtw8822c_get_path_write_addr(path);

	rtw_write32(rtwdev, base_addr + 0x68, 0x0);
	rtw_write32(rtwdev, base_addr + 0x10, 0x02d508c4);
	rtw_write32_mask(rtwdev, base_addr + 0xbc, 0x1, 0x0);
	rtw_write32_mask(rtwdev, base_addr + 0x30, BIT(30), 0x1);
}