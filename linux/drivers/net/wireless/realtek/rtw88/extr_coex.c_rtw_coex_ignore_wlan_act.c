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
struct rtw_coex {scalar_t__ stop_dm; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_fw_bt_ignore_wlan_action (struct rtw_dev*,int) ; 

__attribute__((used)) static void rtw_coex_ignore_wlan_act(struct rtw_dev *rtwdev, bool enable)
{
	struct rtw_coex *coex = &rtwdev->coex;

	if (coex->stop_dm)
		return;

	rtw_fw_bt_ignore_wlan_action(rtwdev, enable);
}