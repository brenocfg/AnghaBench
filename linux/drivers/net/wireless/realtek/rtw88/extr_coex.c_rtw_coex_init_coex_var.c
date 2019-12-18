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
typedef  size_t u8 ;
struct rtw_coex_stat {int /*<<< orphan*/  wl_coex_mode; void** wl_rssi_state; void** bt_rssi_state; scalar_t__* cnt_bt; scalar_t__* cnt_wl; } ;
struct rtw_coex {struct rtw_coex_stat dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_coex coex; } ;
struct rtw_coex_dm {int /*<<< orphan*/  wl_coex_mode; void** wl_rssi_state; void** bt_rssi_state; scalar_t__* cnt_bt; scalar_t__* cnt_wl; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (void**) ; 
 size_t COEX_CNT_BT_MAX ; 
 size_t COEX_CNT_WL_MAX ; 
 void* COEX_RSSI_STATE_LOW ; 
 int /*<<< orphan*/  COEX_WLINK_MAX ; 
 int /*<<< orphan*/  memset (struct rtw_coex_stat*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw_coex_init_coex_var(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	struct rtw_coex_dm *coex_dm = &coex->dm;
	u8 i;

	memset(coex_dm, 0, sizeof(*coex_dm));
	memset(coex_stat, 0, sizeof(*coex_stat));

	for (i = 0; i < COEX_CNT_WL_MAX; i++)
		coex_stat->cnt_wl[i] = 0;

	for (i = 0; i < COEX_CNT_BT_MAX; i++)
		coex_stat->cnt_bt[i] = 0;

	for (i = 0; i < ARRAY_SIZE(coex_dm->bt_rssi_state); i++)
		coex_dm->bt_rssi_state[i] = COEX_RSSI_STATE_LOW;

	for (i = 0; i < ARRAY_SIZE(coex_dm->wl_rssi_state); i++)
		coex_dm->wl_rssi_state[i] = COEX_RSSI_STATE_LOW;

	coex_stat->wl_coex_mode = COEX_WLINK_MAX;
}