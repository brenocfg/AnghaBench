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
typedef  scalar_t__ u8 ;
struct rtw_coex_dm {scalar_t__ cur_bt_pwr_lvl; } ;
struct rtw_coex {struct rtw_coex_dm dm; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_fw_force_bt_tx_power (struct rtw_dev*,scalar_t__) ; 

__attribute__((used)) static void rtw_coex_set_bt_tx_power(struct rtw_dev *rtwdev, u8 bt_pwr_dec_lvl)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_dm *coex_dm = &coex->dm;

	if (bt_pwr_dec_lvl == coex_dm->cur_bt_pwr_lvl)
		return;

	coex_dm->cur_bt_pwr_lvl = bt_pwr_dec_lvl;

	rtw_fw_force_bt_tx_power(rtwdev, bt_pwr_dec_lvl);
}