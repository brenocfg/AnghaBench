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
struct rtw_hal {int rf_path_num; } ;
struct rtw_dev {struct rtw_hal hal; } ;

/* Variables and functions */
 int RTW_RATE_SECTION_MAX ; 
 int /*<<< orphan*/  rtw8822b_set_tx_power_index_by_rate (struct rtw_dev*,int,int) ; 

__attribute__((used)) static void rtw8822b_set_tx_power_index(struct rtw_dev *rtwdev)
{
	struct rtw_hal *hal = &rtwdev->hal;
	int rs, path;

	for (path = 0; path < hal->rf_path_num; path++) {
		for (rs = 0; rs < RTW_RATE_SECTION_MAX; rs++)
			rtw8822b_set_tx_power_index_by_rate(rtwdev, path, rs);
	}
}