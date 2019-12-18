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
struct rtw_lps_conf {int awake_interval; int rlbm; int smart_ps; int /*<<< orphan*/  state; } ;
struct rtw_dev {struct rtw_lps_conf lps_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_LPS_ENABLE ; 
 int /*<<< orphan*/  RTW_FLAG_LEISURE_PS ; 
 int /*<<< orphan*/  RTW_RF_OFF ; 
 int /*<<< orphan*/  rtw_coex_lps_notify (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_flag_set (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_fw_set_pwr_mode (struct rtw_dev*) ; 

__attribute__((used)) static void rtw_enter_lps_core(struct rtw_dev *rtwdev)
{
	struct rtw_lps_conf *conf = &rtwdev->lps_conf;

	conf->state = RTW_RF_OFF;
	conf->awake_interval = 1;
	conf->rlbm = 1;
	conf->smart_ps = 2;

	rtw_coex_lps_notify(rtwdev, COEX_LPS_ENABLE);

	rtw_fw_set_pwr_mode(rtwdev);
	rtw_flag_set(rtwdev, RTW_FLAG_LEISURE_PS);
}