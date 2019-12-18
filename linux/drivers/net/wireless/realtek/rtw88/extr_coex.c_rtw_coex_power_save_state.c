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
struct rtw_vif {int dummy; } ;
struct rtw_lps_conf {int mode; struct rtw_vif* rtwvif; } ;
struct rtw_coex_stat {int wl_force_lps_ctrl; } ;
struct rtw_coex {struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_lps_conf lps_conf; struct rtw_coex coex; } ;

/* Variables and functions */
#define  COEX_PS_LPS_OFF 129 
#define  COEX_PS_WIFI_NATIVE 128 
 int /*<<< orphan*/  rtw_fw_coex_tdma_type (struct rtw_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_in_lps (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_leave_lps (struct rtw_dev*,struct rtw_vif*) ; 

__attribute__((used)) static void rtw_coex_power_save_state(struct rtw_dev *rtwdev, u8 ps_type,
				      u8 lps_val, u8 rpwm_val)
{
	struct rtw_lps_conf *lps_conf = &rtwdev->lps_conf;
	struct rtw_vif *rtwvif;
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	u8 lps_mode = 0x0;

	lps_mode = rtwdev->lps_conf.mode;

	switch (ps_type) {
	case COEX_PS_WIFI_NATIVE:
		/* recover to original 32k low power setting */
		coex_stat->wl_force_lps_ctrl = false;

		rtwvif = lps_conf->rtwvif;
		if (rtwvif && rtw_in_lps(rtwdev))
			rtw_leave_lps(rtwdev, rtwvif);
		break;
	case COEX_PS_LPS_OFF:
		coex_stat->wl_force_lps_ctrl = true;
		if (lps_mode)
			rtw_fw_coex_tdma_type(rtwdev, 0x8, 0, 0, 0, 0);

		rtwvif = lps_conf->rtwvif;
		if (rtwvif && rtw_in_lps(rtwdev))
			rtw_leave_lps(rtwdev, rtwvif);
		break;
	default:
		break;
	}
}