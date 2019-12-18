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
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  rtw_write8_mask (struct rtw_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw8822c_coex_cfg_gnt_debug(struct rtw_dev *rtwdev)
{
	rtw_write8_mask(rtwdev, 0x66, BIT(4), 0);
	rtw_write8_mask(rtwdev, 0x67, BIT(0), 0);
	rtw_write8_mask(rtwdev, 0x42, BIT(3), 0);
	rtw_write8_mask(rtwdev, 0x65, BIT(7), 0);
	rtw_write8_mask(rtwdev, 0x73, BIT(3), 0);
}