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
struct rtw_coex_dm {int cur_ant_pos_type; } ;
struct rtw_coex_stat {int /*<<< orphan*/  bt_disabled; } ;
struct rtw_coex {struct rtw_coex_dm dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_GNT_SET_HW_PTA ; 
 int /*<<< orphan*/  COEX_GNT_SET_SW_HIGH ; 
 int /*<<< orphan*/  COEX_GNT_SET_SW_LOW ; 
#define  COEX_SET_ANT_2G 135 
#define  COEX_SET_ANT_2G_FREERUN 134 
#define  COEX_SET_ANT_2G_WLBT 133 
#define  COEX_SET_ANT_5G 132 
#define  COEX_SET_ANT_INIT 131 
#define  COEX_SET_ANT_POWERON 130 
#define  COEX_SET_ANT_WOFF 129 
#define  COEX_SET_ANT_WONLY 128 
 int COEX_SWITCH_CTRL_BY_BBSW ; 
 int COEX_SWITCH_CTRL_BY_BT ; 
 int COEX_SWITCH_CTRL_BY_PTA ; 
 int COEX_SWITCH_CTRL_MAX ; 
 int COEX_SWITCH_TO_BT ; 
 int COEX_SWITCH_TO_MAX ; 
 int COEX_SWITCH_TO_NOCARE ; 
 int COEX_SWITCH_TO_WLA ; 
 int COEX_SWITCH_TO_WLG ; 
 int COEX_SWITCH_TO_WLG_BT ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  rtw_coex_check_rfk (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_coex_ctrl_owner (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_coex_set_ant_switch (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw_coex_set_gnt_bt (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_gnt_wl (struct rtw_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_coex_set_ant_path(struct rtw_dev *rtwdev, bool force, u8 phase)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	struct rtw_coex_dm *coex_dm = &coex->dm;
	u8 ctrl_type = COEX_SWITCH_CTRL_MAX;
	u8 pos_type = COEX_SWITCH_TO_MAX;

	if (!force && coex_dm->cur_ant_pos_type == phase)
		return;

	coex_dm->cur_ant_pos_type = phase;

	/* avoid switch coex_ctrl_owner during BT IQK */
	rtw_coex_check_rfk(rtwdev);

	switch (phase) {
	case COEX_SET_ANT_POWERON:
		/* set path control owner to BT at power-on */
		if (coex_stat->bt_disabled)
			rtw_coex_coex_ctrl_owner(rtwdev, true);
		else
			rtw_coex_coex_ctrl_owner(rtwdev, false);

		ctrl_type = COEX_SWITCH_CTRL_BY_BBSW;
		pos_type = COEX_SWITCH_TO_BT;
		break;
	case COEX_SET_ANT_INIT:
		if (coex_stat->bt_disabled) {
			/* set GNT_BT to SW low */
			rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_SW_LOW);

			/* set GNT_WL to SW high */
			rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_SW_HIGH);
		} else {
			/* set GNT_BT to SW high */
			rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_SW_HIGH);

			/* set GNT_WL to SW low */
			rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_SW_LOW);
		}

		/* set path control owner to wl at initial step */
		rtw_coex_coex_ctrl_owner(rtwdev, true);

		ctrl_type = COEX_SWITCH_CTRL_BY_BBSW;
		pos_type = COEX_SWITCH_TO_BT;
		break;
	case COEX_SET_ANT_WONLY:
		/* set GNT_BT to SW Low */
		rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_SW_LOW);

		/* Set GNT_WL to SW high */
		rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_SW_HIGH);

		/* set path control owner to wl at initial step */
		rtw_coex_coex_ctrl_owner(rtwdev, true);

		ctrl_type = COEX_SWITCH_CTRL_BY_BBSW;
		pos_type = COEX_SWITCH_TO_WLG;
		break;
	case COEX_SET_ANT_WOFF:
		/* set path control owner to BT */
		rtw_coex_coex_ctrl_owner(rtwdev, false);

		ctrl_type = COEX_SWITCH_CTRL_BY_BT;
		pos_type = COEX_SWITCH_TO_NOCARE;
		break;
	case COEX_SET_ANT_2G:
		/* set GNT_BT to PTA */
		rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_HW_PTA);

		/* set GNT_WL to PTA */
		rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_HW_PTA);

		/* set path control owner to wl at runtime step */
		rtw_coex_coex_ctrl_owner(rtwdev, true);

		ctrl_type = COEX_SWITCH_CTRL_BY_PTA;
		pos_type = COEX_SWITCH_TO_NOCARE;
		break;
	case COEX_SET_ANT_5G:
		/* set GNT_BT to PTA */
		rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_SW_HIGH);

		/* set GNT_WL to SW high */
		rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_SW_HIGH);

		/* set path control owner to wl at runtime step */
		rtw_coex_coex_ctrl_owner(rtwdev, true);

		ctrl_type = COEX_SWITCH_CTRL_BY_BBSW;
		pos_type = COEX_SWITCH_TO_WLA;
		break;
	case COEX_SET_ANT_2G_FREERUN:
		/* set GNT_BT to SW high */
		rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_SW_HIGH);

		/* Set GNT_WL to SW high */
		rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_SW_HIGH);

		/* set path control owner to wl at runtime step */
		rtw_coex_coex_ctrl_owner(rtwdev, true);

		ctrl_type = COEX_SWITCH_CTRL_BY_BBSW;
		pos_type = COEX_SWITCH_TO_WLG_BT;
		break;
	case COEX_SET_ANT_2G_WLBT:
		/* set GNT_BT to SW high */
		rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_HW_PTA);

		/* Set GNT_WL to SW high */
		rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_HW_PTA);

		/* set path control owner to wl at runtime step */
		rtw_coex_coex_ctrl_owner(rtwdev, true);

		ctrl_type = COEX_SWITCH_CTRL_BY_BBSW;
		pos_type = COEX_SWITCH_TO_WLG_BT;
		break;
	default:
		WARN(1, "unknown phase when setting antenna path\n");
		return;
	}

	if (ctrl_type < COEX_SWITCH_CTRL_MAX && pos_type < COEX_SWITCH_TO_MAX)
		rtw_coex_set_ant_switch(rtwdev, ctrl_type, pos_type);
}