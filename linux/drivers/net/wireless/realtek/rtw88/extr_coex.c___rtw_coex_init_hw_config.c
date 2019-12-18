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
struct rtw_coex {int stop_dm; int freeze; scalar_t__ wl_rf_off; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 int COEX_SCBD_ACTIVE ; 
 int COEX_SCBD_ALL ; 
 int COEX_SCBD_SCAN ; 
 int /*<<< orphan*/  COEX_SET_ANT_INIT ; 
 int /*<<< orphan*/  COEX_SET_ANT_WOFF ; 
 int /*<<< orphan*/  COEX_SET_ANT_WONLY ; 
 int /*<<< orphan*/  COEX_WLPRI_TX_BEACON ; 
 int /*<<< orphan*/  COEX_WLPRI_TX_BEACONQ ; 
 int /*<<< orphan*/  COEX_WLPRI_TX_RSP ; 
 int /*<<< orphan*/  rtw_coex_init_coex_var (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_monitor_bt_enable (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_query_bt_info (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_set_ant_path (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_init (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_set_rfe_type (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_set_wl_pri_mask (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_coex_table (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_tdma (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_write_scbd (struct rtw_dev*,int,int) ; 

__attribute__((used)) static void __rtw_coex_init_hw_config(struct rtw_dev *rtwdev, bool wifi_only)
{
	struct rtw_coex *coex = &rtwdev->coex;

	rtw_coex_init_coex_var(rtwdev);
	rtw_coex_monitor_bt_enable(rtwdev);
	rtw_coex_set_rfe_type(rtwdev);
	rtw_coex_set_init(rtwdev);

	/* set Tx response = Hi-Pri (ex: Transmitting ACK,BA,CTS) */
	rtw_coex_set_wl_pri_mask(rtwdev, COEX_WLPRI_TX_RSP, 1);

	/* set Tx beacon = Hi-Pri */
	rtw_coex_set_wl_pri_mask(rtwdev, COEX_WLPRI_TX_BEACON, 1);

	/* set Tx beacon queue = Hi-Pri */
	rtw_coex_set_wl_pri_mask(rtwdev, COEX_WLPRI_TX_BEACONQ, 1);

	/* antenna config */
	if (coex->wl_rf_off) {
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_WOFF);
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_ALL, false);
		coex->stop_dm = true;
	} else if (wifi_only) {
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_WONLY);
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_SCAN,
				    true);
		coex->stop_dm = true;
	} else {
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_INIT);
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_SCAN,
				    true);
		coex->stop_dm = false;
		coex->freeze = true;
	}

	/* PTA parameter */
	rtw_coex_table(rtwdev, 0);
	rtw_coex_tdma(rtwdev, true, 0);
	rtw_coex_query_bt_info(rtwdev);
}