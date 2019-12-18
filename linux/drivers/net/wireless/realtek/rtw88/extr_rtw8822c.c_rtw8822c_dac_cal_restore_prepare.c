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
 int /*<<< orphan*/  rtw8822c_dac_cal_restore_dck (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int,int) ; 

__attribute__((used)) static void rtw8822c_dac_cal_restore_prepare(struct rtw_dev *rtwdev)
{
	rtw_write32(rtwdev, 0x9b4, 0xdb66db00);

	rtw_write32_mask(rtwdev, 0x18b0, BIT(27), 0x0);
	rtw_write32_mask(rtwdev, 0x18cc, BIT(27), 0x0);
	rtw_write32_mask(rtwdev, 0x41b0, BIT(27), 0x0);
	rtw_write32_mask(rtwdev, 0x41cc, BIT(27), 0x0);

	rtw_write32_mask(rtwdev, 0x1830, BIT(30), 0x0);
	rtw_write32_mask(rtwdev, 0x1860, 0xfc000000, 0x3c);
	rtw_write32_mask(rtwdev, 0x18b4, BIT(0), 0x1);
	rtw_write32_mask(rtwdev, 0x18d0, BIT(0), 0x1);

	rtw_write32_mask(rtwdev, 0x4130, BIT(30), 0x0);
	rtw_write32_mask(rtwdev, 0x4160, 0xfc000000, 0x3c);
	rtw_write32_mask(rtwdev, 0x41b4, BIT(0), 0x1);
	rtw_write32_mask(rtwdev, 0x41d0, BIT(0), 0x1);

	rtw_write32_mask(rtwdev, 0x18b0, 0xf00, 0x0);
	rtw_write32_mask(rtwdev, 0x18c0, BIT(14), 0x0);
	rtw_write32_mask(rtwdev, 0x18cc, 0xf00, 0x0);
	rtw_write32_mask(rtwdev, 0x18dc, BIT(14), 0x0);

	rtw_write32_mask(rtwdev, 0x18b0, BIT(0), 0x0);
	rtw_write32_mask(rtwdev, 0x18cc, BIT(0), 0x0);
	rtw_write32_mask(rtwdev, 0x18b0, BIT(0), 0x1);
	rtw_write32_mask(rtwdev, 0x18cc, BIT(0), 0x1);

	rtw8822c_dac_cal_restore_dck(rtwdev);

	rtw_write32_mask(rtwdev, 0x18c0, 0x38000, 0x7);
	rtw_write32_mask(rtwdev, 0x18dc, 0x38000, 0x7);
	rtw_write32_mask(rtwdev, 0x41c0, 0x38000, 0x7);
	rtw_write32_mask(rtwdev, 0x41dc, 0x38000, 0x7);

	rtw_write32_mask(rtwdev, 0x18b8, BIT(26) | BIT(25), 0x1);
	rtw_write32_mask(rtwdev, 0x18d4, BIT(26) | BIT(25), 0x1);

	rtw_write32_mask(rtwdev, 0x41b0, 0xf00, 0x0);
	rtw_write32_mask(rtwdev, 0x41c0, BIT(14), 0x0);
	rtw_write32_mask(rtwdev, 0x41cc, 0xf00, 0x0);
	rtw_write32_mask(rtwdev, 0x41dc, BIT(14), 0x0);

	rtw_write32_mask(rtwdev, 0x41b0, BIT(0), 0x0);
	rtw_write32_mask(rtwdev, 0x41cc, BIT(0), 0x0);
	rtw_write32_mask(rtwdev, 0x41b0, BIT(0), 0x1);
	rtw_write32_mask(rtwdev, 0x41cc, BIT(0), 0x1);

	rtw_write32_mask(rtwdev, 0x41b8, BIT(26) | BIT(25), 0x1);
	rtw_write32_mask(rtwdev, 0x41d4, BIT(26) | BIT(25), 0x1);
}