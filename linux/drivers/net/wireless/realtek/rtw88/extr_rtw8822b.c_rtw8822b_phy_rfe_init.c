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
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int,int) ; 

__attribute__((used)) static void rtw8822b_phy_rfe_init(struct rtw_dev *rtwdev)
{
	/* chip top mux */
	rtw_write32_mask(rtwdev, 0x64, BIT(29) | BIT(28), 0x3);
	rtw_write32_mask(rtwdev, 0x4c, BIT(26) | BIT(25), 0x0);
	rtw_write32_mask(rtwdev, 0x40, BIT(2), 0x1);

	/* from s0 or s1 */
	rtw_write32_mask(rtwdev, 0x1990, 0x3f, 0x30);
	rtw_write32_mask(rtwdev, 0x1990, (BIT(11) | BIT(10)), 0x3);

	/* input or output */
	rtw_write32_mask(rtwdev, 0x974, 0x3f, 0x3f);
	rtw_write32_mask(rtwdev, 0x974, (BIT(11) | BIT(10)), 0x3);
}