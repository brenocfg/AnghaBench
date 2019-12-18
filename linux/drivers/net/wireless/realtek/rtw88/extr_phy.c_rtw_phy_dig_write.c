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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtw_hal {size_t rf_path_num; } ;
struct rtw_dev {struct rtw_hal hal; struct rtw_chip_info* chip; } ;
struct rtw_chip_info {TYPE_1__* dig; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

void rtw_phy_dig_write(struct rtw_dev *rtwdev, u8 igi)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_hal *hal = &rtwdev->hal;
	u32 addr, mask;
	u8 path;

	for (path = 0; path < hal->rf_path_num; path++) {
		addr = chip->dig[path].addr;
		mask = chip->dig[path].mask;
		rtw_write32_mask(rtwdev, addr, mask, igi);
	}
}