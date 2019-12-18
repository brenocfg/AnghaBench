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
typedef  int /*<<< orphan*/  u8 ;
struct rtw_coex_stat {scalar_t__ wl_connected; scalar_t__ wl_linkscan_proc; scalar_t__ bt_inq_page; scalar_t__ bt_setup_link; scalar_t__ bt_whck_test; int /*<<< orphan*/  wl_force_lps_ctrl; scalar_t__ wl_under_lps; scalar_t__ bt_disabled; int /*<<< orphan*/  wl_coex_mode; int /*<<< orphan*/ * cnt_wl; scalar_t__ wl_under_ips; } ;
struct rtw_coex_dm {scalar_t__ bt_status; int /*<<< orphan*/  reason; } ;
struct rtw_coex {int freerun; scalar_t__ under_5g; scalar_t__ freeze; scalar_t__ stop_dm; struct rtw_coex_stat stat; struct rtw_coex_dm dm; } ;
struct rtw_dev {int /*<<< orphan*/  mutex; struct rtw_coex coex; } ;

/* Variables and functions */
 scalar_t__ COEX_BTSTATUS_CON_IDLE ; 
 scalar_t__ COEX_BTSTATUS_NCON_IDLE ; 
 size_t COEX_CNT_WL_COEXRUN ; 
 int /*<<< orphan*/  COEX_SCBD_FIX2M ; 
 int /*<<< orphan*/  COEX_WLINK_2G1PORT ; 
 int /*<<< orphan*/  COEX_WLINK_5G ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_idle (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_inquiry (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_relink (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_whql_test (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_wl_connected (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_wl_linkscan (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_wl_native_lps (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_wl_not_connected (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_wl_only (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_wl_under5g (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_limited_wl (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_monitor_bt_enable (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_set_gnt_fix (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_update_wl_link_info (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_write_scbd (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw_coex_run_coex(struct rtw_dev *rtwdev, u8 reason)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_dm *coex_dm = &coex->dm;
	struct rtw_coex_stat *coex_stat = &coex->stat;

	lockdep_assert_held(&rtwdev->mutex);

	coex_dm->reason = reason;

	/* update wifi_link_info_ext variable */
	rtw_coex_update_wl_link_info(rtwdev, reason);

	rtw_coex_monitor_bt_enable(rtwdev);

	if (coex->stop_dm)
		return;

	if (coex_stat->wl_under_ips)
		return;

	if (coex->freeze && !coex_stat->bt_setup_link)
		return;

	coex_stat->cnt_wl[COEX_CNT_WL_COEXRUN]++;
	coex->freerun = false;

	/* Pure-5G Coex Process */
	if (coex->under_5g) {
		coex_stat->wl_coex_mode = COEX_WLINK_5G;
		rtw_coex_action_wl_under5g(rtwdev);
		goto exit;
	}

	coex_stat->wl_coex_mode = COEX_WLINK_2G1PORT;
	rtw_coex_write_scbd(rtwdev, COEX_SCBD_FIX2M, false);
	if (coex_stat->bt_disabled) {
		rtw_coex_action_wl_only(rtwdev);
		goto exit;
	}

	if (coex_stat->wl_under_lps && !coex_stat->wl_force_lps_ctrl) {
		rtw_coex_action_wl_native_lps(rtwdev);
		goto exit;
	}

	if (coex_stat->bt_whck_test) {
		rtw_coex_action_bt_whql_test(rtwdev);
		goto exit;
	}

	if (coex_stat->bt_setup_link) {
		rtw_coex_action_bt_relink(rtwdev);
		goto exit;
	}

	if (coex_stat->bt_inq_page) {
		rtw_coex_action_bt_inquiry(rtwdev);
		goto exit;
	}

	if ((coex_dm->bt_status == COEX_BTSTATUS_NCON_IDLE ||
	     coex_dm->bt_status == COEX_BTSTATUS_CON_IDLE) &&
	     coex_stat->wl_connected) {
		rtw_coex_action_bt_idle(rtwdev);
		goto exit;
	}

	if (coex_stat->wl_linkscan_proc) {
		rtw_coex_action_wl_linkscan(rtwdev);
		goto exit;
	}

	if (coex_stat->wl_connected)
		rtw_coex_action_wl_connected(rtwdev);
	else
		rtw_coex_action_wl_not_connected(rtwdev);

exit:
	rtw_coex_set_gnt_fix(rtwdev);
	rtw_coex_limited_wl(rtwdev);
}