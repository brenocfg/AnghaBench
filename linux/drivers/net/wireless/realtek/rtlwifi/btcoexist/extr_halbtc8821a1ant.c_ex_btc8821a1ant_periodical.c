#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int dummy; } ;
struct btc_stack_info {int /*<<< orphan*/  hci_version; scalar_t__ profile_notified; } ;
struct btc_board_info {int /*<<< orphan*/  btdm_ant_pos; int /*<<< orphan*/  btdm_ant_num; int /*<<< orphan*/  pg_ant_num; } ;
struct btc_coexist {int /*<<< orphan*/  auto_report_1ant; int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;struct btc_stack_info stack_info; struct btc_board_info board_info; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  special_pkt_period_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_U4_BT_PATCH_VER ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_FW_VER ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  btc8821a1ant_monitor_bt_ctr (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_query_bt_info (struct btc_coexist*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  glcoex_ver_8821a_1ant ; 
 int /*<<< orphan*/  glcoex_ver_date_8821a_1ant ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ex_btc8821a1ant_periodical(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	static u8 dis_ver_info_cnt;
	u32 fw_ver = 0, bt_patch_ver = 0;
	struct btc_board_info *board_info = &btcoexist->board_info;
	struct btc_stack_info *stack_info = &btcoexist->stack_info;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], ==========================Periodical===========================\n");

	if (dis_ver_info_cnt <= 5) {
		dis_ver_info_cnt += 1;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], ****************************************************************\n");
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Ant PG Num/ Ant Mech/ Ant Pos = %d/ %d/ %d\n",
			      board_info->pg_ant_num,
			      board_info->btdm_ant_num,
			      board_info->btdm_ant_pos);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT stack/ hci ext ver = %s / %d\n",
			      stack_info->profile_notified ? "Yes" : "No",
			      stack_info->hci_version);
		btcoexist->btc_get(btcoexist, BTC_GET_U4_BT_PATCH_VER,
				   &bt_patch_ver);
		btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], CoexVer/ FwVer/ PatchVer = %d_%x/ 0x%x/ 0x%x(%d)\n",
			      glcoex_ver_date_8821a_1ant,
			      glcoex_ver_8821a_1ant,
			      fw_ver, bt_patch_ver,
			      bt_patch_ver);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], ****************************************************************\n");
	}

	if (!btcoexist->auto_report_1ant) {
		btc8821a1ant_query_bt_info(btcoexist);
		btc8821a1ant_monitor_bt_ctr(btcoexist);
	} else {
		coex_sta->special_pkt_period_cnt++;
	}
}