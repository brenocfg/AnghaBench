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
struct rtw_coex_stat {int wl_hi_pri_task1; int* cnt_wl; } ;
struct rtw_coex {int freeze; int /*<<< orphan*/  defreeze_work; scalar_t__ stop_dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {int /*<<< orphan*/  hw; struct rtw_coex coex; } ;

/* Variables and functions */
 scalar_t__ COEX_ASSOCIATE_5G_FINISH ; 
 scalar_t__ COEX_ASSOCIATE_5G_START ; 
 scalar_t__ COEX_ASSOCIATE_START ; 
 size_t COEX_CNT_WL_CONNPKT ; 
 int /*<<< orphan*/  COEX_RSN_2GCONFINISH ; 
 int /*<<< orphan*/  COEX_RSN_2GCONSTART ; 
 int /*<<< orphan*/  COEX_RSN_5GCONFINISH ; 
 int /*<<< orphan*/  COEX_RSN_5GCONSTART ; 
 int COEX_SCBD_ACTIVE ; 
 int COEX_SCBD_ONOFF ; 
 int COEX_SCBD_SCAN ; 
 int /*<<< orphan*/  COEX_SET_ANT_2G ; 
 int /*<<< orphan*/  COEX_SET_ANT_5G ; 
 int HZ ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtw_coex_run_coex (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_ant_path (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_write_scbd (struct rtw_dev*,int,int) ; 

void rtw_coex_connect_notify(struct rtw_dev *rtwdev, u8 type)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;

	if (coex->stop_dm)
		return;

	rtw_coex_write_scbd(rtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_SCAN |
			    COEX_SCBD_ONOFF, true);

	if (type == COEX_ASSOCIATE_5G_START) {
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_5G);
		rtw_coex_run_coex(rtwdev, COEX_RSN_5GCONSTART);
	} else if (type == COEX_ASSOCIATE_5G_FINISH) {
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_5G);
		rtw_coex_run_coex(rtwdev, COEX_RSN_5GCONFINISH);
	} else if (type == COEX_ASSOCIATE_START) {
		coex_stat->wl_hi_pri_task1 = true;
		coex_stat->cnt_wl[COEX_CNT_WL_CONNPKT] = 2;

		/* Force antenna setup for no scan result issue */
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_2G);

		rtw_coex_run_coex(rtwdev, COEX_RSN_2GCONSTART);

		/* To keep TDMA case during connect process,
		 * to avoid changed by Btinfo and runcoexmechanism
		 */
		coex->freeze = true;
		ieee80211_queue_delayed_work(rtwdev->hw, &coex->defreeze_work,
					     5 * HZ);
	} else {
		coex_stat->wl_hi_pri_task1 = false;
		coex->freeze = false;

		rtw_coex_run_coex(rtwdev, COEX_RSN_2GCONFINISH);
	}
}