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
typedef  scalar_t__ u8 ;
struct rtw_hal {scalar_t__ rf_path_num; int /*<<< orphan*/  tx_power_mutex; } ;
struct rtw_dev {struct rtw_hal hal; struct rtw_chip_info* chip; } ;
struct rtw_chip_info {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_tx_power_index ) (struct rtw_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_phy_set_tx_power_level_by_path (struct rtw_dev*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct rtw_dev*) ; 

void rtw_phy_set_tx_power_level(struct rtw_dev *rtwdev, u8 channel)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_hal *hal = &rtwdev->hal;
	u8 path;

	mutex_lock(&hal->tx_power_mutex);

	for (path = 0; path < hal->rf_path_num; path++)
		rtw_phy_set_tx_power_level_by_path(rtwdev, channel, path);

	chip->ops->set_tx_power_index(rtwdev);
	mutex_unlock(&hal->tx_power_mutex);
}