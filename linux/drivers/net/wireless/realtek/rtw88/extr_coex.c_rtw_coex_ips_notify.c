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
struct rtw_coex_stat {int wl_under_ips; } ;
struct rtw_coex {scalar_t__ stop_dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 scalar_t__ COEX_IPS_ENTER ; 
 scalar_t__ COEX_IPS_LEAVE ; 
 int COEX_SCBD_ACTIVE ; 
 int COEX_SCBD_ALL ; 
 int COEX_SCBD_ONOFF ; 
 int /*<<< orphan*/  COEX_SET_ANT_WOFF ; 
 int /*<<< orphan*/  __rtw_coex_init_hw_config (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_coex_action_coex_all_off (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_set_ant_path (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_write_scbd (struct rtw_dev*,int,int) ; 

void rtw_coex_ips_notify(struct rtw_dev *rtwdev, u8 type)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;

	if (coex->stop_dm)
		return;

	if (type == COEX_IPS_ENTER) {
		coex_stat->wl_under_ips = true;

		/* for lps off */
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_ALL, false);

		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_WOFF);
		rtw_coex_action_coex_all_off(rtwdev);
	} else if (type == COEX_IPS_LEAVE) {
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_ONOFF, true);

		/* run init hw config (exclude wifi only) */
		__rtw_coex_init_hw_config(rtwdev, false);
		/* sw all off */

		coex_stat->wl_under_ips = false;
	}
}