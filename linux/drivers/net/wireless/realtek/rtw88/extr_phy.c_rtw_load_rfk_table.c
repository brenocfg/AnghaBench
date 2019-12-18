#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtw_dpk_info {int is_dpk_pwr_on; } ;
struct TYPE_2__ {struct rtw_dpk_info dpk_info; } ;
struct rtw_dev {TYPE_1__ dm_info; struct rtw_chip_info* chip; } ;
struct rtw_chip_info {int /*<<< orphan*/  rfk_init_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  rtw_load_table (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw_load_rfk_table(struct rtw_dev *rtwdev)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;

	if (!chip->rfk_init_tbl)
		return;

	rtw_write32_mask(rtwdev, 0x1e24, BIT(17), 0x1);
	rtw_write32_mask(rtwdev, 0x1cd0, BIT(28), 0x1);
	rtw_write32_mask(rtwdev, 0x1cd0, BIT(29), 0x1);
	rtw_write32_mask(rtwdev, 0x1cd0, BIT(30), 0x1);
	rtw_write32_mask(rtwdev, 0x1cd0, BIT(31), 0x0);

	rtw_load_table(rtwdev, chip->rfk_init_tbl);

	dpk_info->is_dpk_pwr_on = 1;
}