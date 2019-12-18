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
struct rtw_coex_stat {int wl_slot_extend; } ;
struct rtw_coex {scalar_t__ stop_dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 scalar_t__ COEX_H2C69_WL_LEAKAP ; 
 scalar_t__ COEX_MEDIA_CONNECT ; 
 scalar_t__ COEX_MEDIA_CONNECT_5G ; 
 int /*<<< orphan*/  COEX_RSN_2GMEDIA ; 
 int /*<<< orphan*/  COEX_RSN_5GMEDIA ; 
 int /*<<< orphan*/  COEX_RSN_MEDIADISCON ; 
 int /*<<< orphan*/  COEX_SCBD_ACTIVE ; 
 int /*<<< orphan*/  COEX_SET_ANT_2G ; 
 int /*<<< orphan*/  COEX_SET_ANT_5G ; 
 int /*<<< orphan*/  COEX_WLPRI_RX_CCK ; 
 scalar_t__ PARA1_H2C69_EN_5MS ; 
 int /*<<< orphan*/  rtw_coex_run_coex (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_ant_path (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_wl_pri_mask (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_coex_update_wl_ch_info (struct rtw_dev*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_coex_write_scbd (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_fw_bt_wifi_control (struct rtw_dev*,scalar_t__,scalar_t__*) ; 

void rtw_coex_media_status_notify(struct rtw_dev *rtwdev, u8 type)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	u8 para[6] = {0};

	if (coex->stop_dm)
		return;

	if (type == COEX_MEDIA_CONNECT_5G) {
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_ACTIVE, true);

		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_5G);
		rtw_coex_run_coex(rtwdev, COEX_RSN_5GMEDIA);
	} else if (type == COEX_MEDIA_CONNECT) {
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_ACTIVE, true);

		/* Force antenna setup for no scan result issue */
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_2G);

		/* Set CCK Rx high Pri */
		rtw_coex_set_wl_pri_mask(rtwdev, COEX_WLPRI_RX_CCK, 1);

		/* always enable 5ms extend if connect */
		para[0] = COEX_H2C69_WL_LEAKAP;
		para[1] = PARA1_H2C69_EN_5MS; /* enable 5ms extend */
		rtw_fw_bt_wifi_control(rtwdev, para[0], &para[1]);
		coex_stat->wl_slot_extend = true;
		rtw_coex_run_coex(rtwdev, COEX_RSN_2GMEDIA);
	} else {
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_ACTIVE, false);

		rtw_coex_set_wl_pri_mask(rtwdev, COEX_WLPRI_RX_CCK, 0);

		rtw_coex_run_coex(rtwdev, COEX_RSN_MEDIADISCON);
	}

	rtw_coex_update_wl_ch_info(rtwdev, type);
}