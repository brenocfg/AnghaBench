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
 int /*<<< orphan*/  COEX_RSN_WLSTATUS ; 
 int /*<<< orphan*/  rtw_coex_run_coex (struct rtw_dev*,int /*<<< orphan*/ ) ; 

void rtw_coex_wl_status_change_notify(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;

	if (coex->stop_dm)
		return;

	rtw_coex_run_coex(rtwdev, COEX_RSN_WLSTATUS);
}