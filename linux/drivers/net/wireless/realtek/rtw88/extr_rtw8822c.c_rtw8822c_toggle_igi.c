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
 int /*<<< orphan*/  REG_RXIGI ; 
 scalar_t__ rtw_read32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static void rtw8822c_toggle_igi(struct rtw_dev *rtwdev)
{
	u32 igi;

	igi = rtw_read32_mask(rtwdev, REG_RXIGI, 0x7f);
	rtw_write32_mask(rtwdev, REG_RXIGI, 0x7f, igi - 2);
	rtw_write32_mask(rtwdev, REG_RXIGI, 0x7f00, igi - 2);
	rtw_write32_mask(rtwdev, REG_RXIGI, 0x7f, igi);
	rtw_write32_mask(rtwdev, REG_RXIGI, 0x7f00, igi);
}