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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int,int) ; 

__attribute__((used)) static void rtw8822c_dac_bb_setting(struct rtw_dev *rtwdev)
{
	rtw_write32_mask(rtwdev, 0x1d58, 0xff8, 0x1ff);
	rtw_write32_mask(rtwdev, 0x1a00, 0x3, 0x2);
	rtw_write32_mask(rtwdev, 0x1a14, 0x300, 0x3);
	rtw_write32(rtwdev, 0x1d70, 0x7e7e7e7e);
	rtw_write32_mask(rtwdev, 0x180c, 0x3, 0x0);
	rtw_write32_mask(rtwdev, 0x410c, 0x3, 0x0);
	rtw_write32(rtwdev, 0x1b00, 0x00000008);
	rtw_write8(rtwdev, 0x1bcc, 0x3f);
	rtw_write32(rtwdev, 0x1b00, 0x0000000a);
	rtw_write8(rtwdev, 0x1bcc, 0x3f);
	rtw_write32_mask(rtwdev, 0x1e24, BIT(31), 0x0);
	rtw_write32_mask(rtwdev, 0x1e28, 0xf, 0x3);
}