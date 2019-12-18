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
typedef  int u32 ;
struct rtw_dm_info {int cck_ok_cnt; int cck_err_cnt; } ;
struct rtw_coex_stat {int* cnt_wl; int wl_noisy_level; int /*<<< orphan*/  wl_gl_busy; } ;
struct rtw_coex {struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_dm_info dm_info; struct rtw_coex coex; } ;

/* Variables and functions */
 size_t COEX_CNT_WL_NOISY0 ; 
 size_t COEX_CNT_WL_NOISY1 ; 
 size_t COEX_CNT_WL_NOISY2 ; 

__attribute__((used)) static void rtw_coex_wl_noisy_detect(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	struct rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 cnt_cck;

	/* wifi noisy environment identification */
	cnt_cck = dm_info->cck_ok_cnt + dm_info->cck_err_cnt;

	if (!coex_stat->wl_gl_busy) {
		if (cnt_cck > 250) {
			if (coex_stat->cnt_wl[COEX_CNT_WL_NOISY2] < 5)
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY2]++;

			if (coex_stat->cnt_wl[COEX_CNT_WL_NOISY2] == 5) {
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY0] = 0;
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY1] = 0;
			}
		} else if (cnt_cck < 100) {
			if (coex_stat->cnt_wl[COEX_CNT_WL_NOISY0] < 5)
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY0]++;

			if (coex_stat->cnt_wl[COEX_CNT_WL_NOISY0] == 5) {
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY1] = 0;
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY2] = 0;
			}
		} else {
			if (coex_stat->cnt_wl[COEX_CNT_WL_NOISY1] < 5)
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY1]++;

			if (coex_stat->cnt_wl[COEX_CNT_WL_NOISY1] == 5) {
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY0] = 0;
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY2] = 0;
			}
		}

		if (coex_stat->cnt_wl[COEX_CNT_WL_NOISY2] == 5)
			coex_stat->wl_noisy_level = 2;
		else if (coex_stat->cnt_wl[COEX_CNT_WL_NOISY1] == 5)
			coex_stat->wl_noisy_level = 1;
		else
			coex_stat->wl_noisy_level = 0;
	}
}