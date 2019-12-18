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
struct rtw_coex {int stop_dm; int wl_rf_off; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COEX_SET_ANT_POWERON ; 
 int /*<<< orphan*/  REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  rtw_coex_monitor_bt_enable (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_set_ant_path (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_rfe_type (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_write8_set (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

void rtw_coex_power_on_setting(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;

	coex->stop_dm = true;
	coex->wl_rf_off = false;

	/* enable BB, we can write 0x948 */
	rtw_write8_set(rtwdev, REG_SYS_FUNC_EN, BIT(0) | BIT(1));

	rtw_coex_monitor_bt_enable(rtwdev);
	rtw_coex_set_rfe_type(rtwdev);

	/* set antenna path to BT */
	rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_POWERON);

	/* red x issue */
	rtw_write8(rtwdev, 0xff1a, 0x0);
}