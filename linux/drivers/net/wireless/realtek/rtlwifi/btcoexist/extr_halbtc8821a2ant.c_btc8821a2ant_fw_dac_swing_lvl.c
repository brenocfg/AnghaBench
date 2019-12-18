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
typedef  char* u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;
struct TYPE_2__ {char* cur_fw_dac_swing_lvl; char* pre_fw_dac_swing_lvl; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  btc8821a2ant_set_fw_dac_swing_lvl (struct btc_coexist*,char*) ; 
 TYPE_1__* coex_dm ; 

__attribute__((used)) static void btc8821a2ant_fw_dac_swing_lvl(struct btc_coexist *btcoexist,
					  bool force_exec, u8 fw_dac_swing_lvl)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], %s set FW Dac Swing level = %d\n",
		 (force_exec ? "force to" : ""), fw_dac_swing_lvl);
	coex_dm->cur_fw_dac_swing_lvl = fw_dac_swing_lvl;

	if (!force_exec) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], pre_fw_dac_swing_lvl = %d, cur_fw_dac_swing_lvl = %d\n",
			 coex_dm->pre_fw_dac_swing_lvl,
			 coex_dm->cur_fw_dac_swing_lvl);

		if (coex_dm->pre_fw_dac_swing_lvl ==
		    coex_dm->cur_fw_dac_swing_lvl)
			return;
	}

	btc8821a2ant_set_fw_dac_swing_lvl(btcoexist,
					  coex_dm->cur_fw_dac_swing_lvl);

	coex_dm->pre_fw_dac_swing_lvl = coex_dm->cur_fw_dac_swing_lvl;
}