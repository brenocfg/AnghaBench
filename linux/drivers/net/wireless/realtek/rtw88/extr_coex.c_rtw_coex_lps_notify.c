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
struct rtw_coex_stat {int wl_under_lps; scalar_t__ wl_force_lps_ctrl; } ;
struct rtw_coex {scalar_t__ stop_dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 scalar_t__ COEX_LPS_DISABLE ; 
 scalar_t__ COEX_LPS_ENABLE ; 
 int /*<<< orphan*/  COEX_RSN_LPS ; 
 int /*<<< orphan*/  COEX_SCBD_ACTIVE ; 
 int /*<<< orphan*/  rtw_coex_query_bt_info (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_run_coex (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_write_scbd (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

void rtw_coex_lps_notify(struct rtw_dev *rtwdev, u8 type)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;

	if (coex->stop_dm)
		return;

	if (type == COEX_LPS_ENABLE) {
		coex_stat->wl_under_lps = true;

		if (coex_stat->wl_force_lps_ctrl) {
			/* for ps-tdma */
			rtw_coex_write_scbd(rtwdev, COEX_SCBD_ACTIVE, true);
		} else {
			/* for native ps */
			rtw_coex_write_scbd(rtwdev, COEX_SCBD_ACTIVE, false);

			rtw_coex_run_coex(rtwdev, COEX_RSN_LPS);
		}
	} else if (type == COEX_LPS_DISABLE) {
		coex_stat->wl_under_lps = false;

		/* for lps off */
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_ACTIVE, true);

		if (!coex_stat->wl_force_lps_ctrl)
			rtw_coex_query_bt_info(rtwdev);
	}
}