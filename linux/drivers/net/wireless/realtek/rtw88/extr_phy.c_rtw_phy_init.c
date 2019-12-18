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
typedef  int /*<<< orphan*/  u32 ;
struct rtw_dm_info {scalar_t__* igi_history; scalar_t__ igi_bitmap; scalar_t__* fa_history; } ;
struct rtw_dev {struct rtw_dm_info dm_info; struct rtw_chip_info* chip; } ;
struct rtw_chip_info {TYPE_1__* dig; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_phy_cck_pd_init (struct rtw_dev*) ; 
 scalar_t__ rtw_read32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtw_phy_init(struct rtw_dev *rtwdev)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 addr, mask;

	dm_info->fa_history[3] = 0;
	dm_info->fa_history[2] = 0;
	dm_info->fa_history[1] = 0;
	dm_info->fa_history[0] = 0;
	dm_info->igi_bitmap = 0;
	dm_info->igi_history[3] = 0;
	dm_info->igi_history[2] = 0;
	dm_info->igi_history[1] = 0;

	addr = chip->dig[0].addr;
	mask = chip->dig[0].mask;
	dm_info->igi_history[0] = rtw_read32_mask(rtwdev, addr, mask);
	rtw_phy_cck_pd_init(rtwdev);
}