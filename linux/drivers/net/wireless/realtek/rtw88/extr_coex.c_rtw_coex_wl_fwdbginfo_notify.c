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
struct rtw_coex_stat {int* wl_fw_dbg_info_pre; int* wl_fw_dbg_info; int /*<<< orphan*/ * cnt_wl; } ;
struct rtw_coex {struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 size_t COEX_CNT_WL_FW_NOTIFY ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  rtw_coex_wl_ccklock_action (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_wl_ccklock_detect (struct rtw_dev*) ; 

void rtw_coex_wl_fwdbginfo_notify(struct rtw_dev *rtwdev, u8 *buf, u8 length)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	u8 val;
	int i;

	if (WARN(length < 8, "invalid wl info c2h length\n"))
		return;

	if (buf[0] != 0x08)
		return;

	for (i = 1; i < 8; i++) {
		val = coex_stat->wl_fw_dbg_info_pre[i];
		if (buf[i] >= val)
			coex_stat->wl_fw_dbg_info[i] = buf[i] - val;
		else
			coex_stat->wl_fw_dbg_info[i] = val - buf[i];

		coex_stat->wl_fw_dbg_info_pre[i] = buf[i];
	}

	coex_stat->cnt_wl[COEX_CNT_WL_FW_NOTIFY]++;
	rtw_coex_wl_ccklock_action(rtwdev);
	rtw_coex_wl_ccklock_detect(rtwdev);
}