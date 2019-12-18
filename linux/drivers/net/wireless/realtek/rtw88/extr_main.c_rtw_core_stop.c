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
struct rtw_coex {int /*<<< orphan*/  defreeze_work; int /*<<< orphan*/  bt_reenable_work; int /*<<< orphan*/  bt_relink_work; } ;
struct rtw_dev {int /*<<< orphan*/  watch_dog_work; struct rtw_coex coex; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_FLAG_FW_RUNNING ; 
 int /*<<< orphan*/  RTW_FLAG_RUNNING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_flag_clear (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_power_off (struct rtw_dev*) ; 

void rtw_core_stop(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;

	rtw_flag_clear(rtwdev, RTW_FLAG_RUNNING);
	rtw_flag_clear(rtwdev, RTW_FLAG_FW_RUNNING);

	cancel_delayed_work_sync(&rtwdev->watch_dog_work);
	cancel_delayed_work_sync(&coex->bt_relink_work);
	cancel_delayed_work_sync(&coex->bt_reenable_work);
	cancel_delayed_work_sync(&coex->defreeze_work);

	rtw_power_off(rtwdev);
}