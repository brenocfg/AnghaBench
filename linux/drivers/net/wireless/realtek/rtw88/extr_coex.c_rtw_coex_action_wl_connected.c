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
struct rtw_efuse {int /*<<< orphan*/  share_ant; } ;
struct rtw_coex_dm {int /*<<< orphan*/ * bt_rssi_state; int /*<<< orphan*/ * wl_rssi_state; } ;
struct rtw_coex_stat {int /*<<< orphan*/  bt_a2dp_sink; scalar_t__ wl_gl_busy; } ;
struct rtw_coex {struct rtw_coex_dm dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_efuse efuse; struct rtw_coex coex; } ;

/* Variables and functions */
#define  COEX_ALGO_A2DP 136 
#define  COEX_ALGO_A2DP_HID 135 
#define  COEX_ALGO_A2DP_PAN 134 
#define  COEX_ALGO_A2DP_PAN_HID 133 
#define  COEX_ALGO_HFP 132 
#define  COEX_ALGO_HID 131 
#define  COEX_ALGO_NOPROFILE 130 
#define  COEX_ALGO_PAN 129 
#define  COEX_ALGO_PAN_HID 128 
 scalar_t__ COEX_RSSI_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_a2dp (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_a2dp_hid (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_a2dp_pan (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_a2dp_pan_hid (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_a2dpsink (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_hfp (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_hid (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_idle (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_pan (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_bt_pan_hid (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_action_freerun (struct rtw_dev*) ; 
 int rtw_coex_algorithm (struct rtw_dev*) ; 

__attribute__((used)) static void rtw_coex_action_wl_connected(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	struct rtw_coex_dm *coex_dm = &coex->dm;
	struct rtw_efuse *efuse = &rtwdev->efuse;
	u8 algorithm;

	/* Non-Shared-Ant */
	if (!efuse->share_ant && coex_stat->wl_gl_busy &&
	    COEX_RSSI_HIGH(coex_dm->wl_rssi_state[3]) &&
	    COEX_RSSI_HIGH(coex_dm->bt_rssi_state[0])) {
		rtw_coex_action_freerun(rtwdev);
		return;
	}

	algorithm = rtw_coex_algorithm(rtwdev);

	switch (algorithm) {
	case COEX_ALGO_HFP:
		rtw_coex_action_bt_hfp(rtwdev);
		break;
	case COEX_ALGO_HID:
		rtw_coex_action_bt_hid(rtwdev);
		break;
	case COEX_ALGO_A2DP:
		if (coex_stat->bt_a2dp_sink)
			rtw_coex_action_bt_a2dpsink(rtwdev);
		else
			rtw_coex_action_bt_a2dp(rtwdev);
		break;
	case COEX_ALGO_PAN:
		rtw_coex_action_bt_pan(rtwdev);
		break;
	case COEX_ALGO_A2DP_HID:
		rtw_coex_action_bt_a2dp_hid(rtwdev);
		break;
	case COEX_ALGO_A2DP_PAN:
		rtw_coex_action_bt_a2dp_pan(rtwdev);
		break;
	case COEX_ALGO_PAN_HID:
		rtw_coex_action_bt_pan_hid(rtwdev);
		break;
	case COEX_ALGO_A2DP_PAN_HID:
		rtw_coex_action_bt_a2dp_pan_hid(rtwdev);
		break;
	default:
	case COEX_ALGO_NOPROFILE:
		rtw_coex_action_bt_idle(rtwdev);
		break;
	}
}