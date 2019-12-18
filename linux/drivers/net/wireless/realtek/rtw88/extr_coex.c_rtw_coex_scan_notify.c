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
struct rtw_coex_stat {int wl_hi_pri_task2; } ;
struct rtw_coex {int freeze; scalar_t__ stop_dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_RSN_2GSCANSTART ; 
 int /*<<< orphan*/  COEX_RSN_5GSCANSTART ; 
 int /*<<< orphan*/  COEX_RSN_SCANFINISH ; 
 scalar_t__ COEX_SCAN_FINISH ; 
 scalar_t__ COEX_SCAN_START ; 
 scalar_t__ COEX_SCAN_START_2G ; 
 scalar_t__ COEX_SCAN_START_5G ; 
 int COEX_SCBD_ACTIVE ; 
 int COEX_SCBD_ONOFF ; 
 int COEX_SCBD_SCAN ; 
 int /*<<< orphan*/  COEX_SET_ANT_2G ; 
 int /*<<< orphan*/  COEX_SET_ANT_5G ; 
 int /*<<< orphan*/  rtw_coex_run_coex (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_ant_path (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_write_scbd (struct rtw_dev*,int,int) ; 

void rtw_coex_scan_notify(struct rtw_dev *rtwdev, u8 type)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;

	if (coex->stop_dm)
		return;

	coex->freeze = false;

	if (type != COEX_SCAN_FINISH)
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_SCAN |
				    COEX_SCBD_ONOFF, true);

	if (type == COEX_SCAN_START_5G) {
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_5G);
		rtw_coex_run_coex(rtwdev, COEX_RSN_5GSCANSTART);
	} else if ((type == COEX_SCAN_START_2G) || (type == COEX_SCAN_START)) {
		coex_stat->wl_hi_pri_task2 = true;

		/* Force antenna setup for no scan result issue */
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_2G);
		rtw_coex_run_coex(rtwdev, COEX_RSN_2GSCANSTART);
	} else {
		coex_stat->wl_hi_pri_task2 = false;
		rtw_coex_run_coex(rtwdev, COEX_RSN_SCANFINISH);
	}
}