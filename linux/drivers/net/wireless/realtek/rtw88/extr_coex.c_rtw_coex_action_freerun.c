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
struct rtw_efuse {scalar_t__ share_ant; } ;
struct rtw_coex_dm {int /*<<< orphan*/ * wl_rssi_state; } ;
struct rtw_coex_stat {scalar_t__ wl_tput_dir; scalar_t__ wl_connected; } ;
struct rtw_coex {int freerun; struct rtw_coex_dm dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_chip_info* chip; struct rtw_efuse efuse; struct rtw_coex coex; } ;
struct rtw_chip_info {int wl_rf_para_num; int /*<<< orphan*/ * wl_rf_para_rx; int /*<<< orphan*/ * wl_rf_para_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_MEDIA_CONNECT ; 
 scalar_t__ COEX_RSSI_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COEX_SCBD_FIX2M ; 
 int /*<<< orphan*/  COEX_SET_ANT_2G_FREERUN ; 
 scalar_t__ COEX_WL_TPUT_TX ; 
 int /*<<< orphan*/  rtw_coex_set_ant_path (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_rf_para (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_table (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_coex_tdma (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_coex_update_wl_ch_info (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_write_scbd (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw_coex_action_freerun(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	struct rtw_coex_dm *coex_dm = &coex->dm;
	struct rtw_efuse *efuse = &rtwdev->efuse;
	struct rtw_chip_info *chip = rtwdev->chip;
	u8 level = 0;

	if (efuse->share_ant)
		return;

	coex->freerun = true;

	if (coex_stat->wl_connected)
		rtw_coex_update_wl_ch_info(rtwdev, COEX_MEDIA_CONNECT);

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G_FREERUN);

	rtw_coex_write_scbd(rtwdev, COEX_SCBD_FIX2M, false);

	if (COEX_RSSI_HIGH(coex_dm->wl_rssi_state[0]))
		level = 2;
	else if (COEX_RSSI_HIGH(coex_dm->wl_rssi_state[1]))
		level = 3;
	else if (COEX_RSSI_HIGH(coex_dm->wl_rssi_state[2]))
		level = 4;
	else
		level = 5;

	if (level > chip->wl_rf_para_num - 1)
		level = chip->wl_rf_para_num - 1;

	if (coex_stat->wl_tput_dir == COEX_WL_TPUT_TX)
		rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_tx[level]);
	else
		rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[level]);

	rtw_coex_table(rtwdev, 100);
	rtw_coex_tdma(rtwdev, false, 100);
}