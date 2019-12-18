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
struct rtw_coex {scalar_t__ stop_dm; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_RSN_2GSWITCHBAND ; 
 int /*<<< orphan*/  COEX_RSN_5GSWITCHBAND ; 
 int /*<<< orphan*/  COEX_SCAN_START_2G ; 
 scalar_t__ COEX_SWITCH_TO_24G_NOFORSCAN ; 
 scalar_t__ COEX_SWITCH_TO_5G ; 
 int /*<<< orphan*/  rtw_coex_run_coex (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_scan_notify (struct rtw_dev*,int /*<<< orphan*/ ) ; 

void rtw_coex_switchband_notify(struct rtw_dev *rtwdev, u8 type)
{
	struct rtw_coex *coex = &rtwdev->coex;

	if (coex->stop_dm)
		return;

	if (type == COEX_SWITCH_TO_5G)
		rtw_coex_run_coex(rtwdev, COEX_RSN_5GSWITCHBAND);
	else if (type == COEX_SWITCH_TO_24G_NOFORSCAN)
		rtw_coex_run_coex(rtwdev, COEX_RSN_2GSWITCHBAND);
	else
		rtw_coex_scan_notify(rtwdev, COEX_SCAN_START_2G);
}