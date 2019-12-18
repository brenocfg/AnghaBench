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
typedef  int u8 ;
struct rtw_coex_stat {int tdma_timer_base; int wl_slot_extend; int* cnt_wl; int* wl_fw_dbg_info; scalar_t__ wl_cck_lock; int /*<<< orphan*/  wl_cck_lock_ever; scalar_t__ wl_force_lps_ctrl; } ;
struct rtw_coex {scalar_t__ stop_dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 size_t COEX_CNT_WL_5MS_NOEXTEND ; 
 int COEX_H2C69_WL_LEAKAP ; 
 int PARA1_H2C69_DIS_5MS ; 
 int /*<<< orphan*/  rtw_fw_bt_wifi_control (struct rtw_dev*,int,int*) ; 

__attribute__((used)) static void rtw_coex_wl_ccklock_action(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	u8 para[6] = {0};

	if (coex->stop_dm)
		return;

	para[0] = COEX_H2C69_WL_LEAKAP;

	if (coex_stat->tdma_timer_base == 3 && coex_stat->wl_slot_extend) {
		para[1] = PARA1_H2C69_DIS_5MS; /* disable 5ms extend */
		rtw_fw_bt_wifi_control(rtwdev, para[0], &para[1]);
		coex_stat->wl_slot_extend = false;
		coex_stat->cnt_wl[COEX_CNT_WL_5MS_NOEXTEND] = 0;
		return;
	}

	if (coex_stat->wl_slot_extend && coex_stat->wl_force_lps_ctrl &&
	    !coex_stat->wl_cck_lock_ever) {
		if (coex_stat->wl_fw_dbg_info[7] <= 5)
			coex_stat->cnt_wl[COEX_CNT_WL_5MS_NOEXTEND]++;
		else
			coex_stat->cnt_wl[COEX_CNT_WL_5MS_NOEXTEND] = 0;

		if (coex_stat->cnt_wl[COEX_CNT_WL_5MS_NOEXTEND] == 7) {
			para[1] = 0x1; /* disable 5ms extend */
			rtw_fw_bt_wifi_control(rtwdev, para[0], &para[1]);
			coex_stat->wl_slot_extend = false;
			coex_stat->cnt_wl[COEX_CNT_WL_5MS_NOEXTEND] = 0;
		}
	} else if (!coex_stat->wl_slot_extend && coex_stat->wl_cck_lock) {
		para[1] = 0x0; /* enable 5ms extend */
		rtw_fw_bt_wifi_control(rtwdev, para[0], &para[1]);
		coex_stat->wl_slot_extend = true;
	}
}