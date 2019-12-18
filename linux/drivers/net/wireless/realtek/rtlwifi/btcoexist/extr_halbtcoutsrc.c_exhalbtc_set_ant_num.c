#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct TYPE_6__ {int /*<<< orphan*/  btdm_ant_pos; scalar_t__ btdm_ant_num; scalar_t__ pg_ant_num; } ;
struct btc_coexist {TYPE_3__ board_info; } ;
struct TYPE_5__ {TYPE_1__* mod_params; } ;
struct TYPE_4__ {int ant_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANTENNA_AT_AUX_PORT ; 
 int /*<<< orphan*/  BTC_ANTENNA_AT_MAIN_PORT ; 
 scalar_t__ BT_COEX_ANT_TYPE_ANTDIV ; 
 scalar_t__ BT_COEX_ANT_TYPE_DETECTED ; 
 scalar_t__ BT_COEX_ANT_TYPE_PG ; 
 struct btc_coexist* rtl_btc_coexist (struct rtl_priv*) ; 

void exhalbtc_set_ant_num(struct rtl_priv *rtlpriv, u8 type, u8 ant_num)
{
	struct btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	if (!btcoexist)
		return;

	if (BT_COEX_ANT_TYPE_PG == type) {
		btcoexist->board_info.pg_ant_num = ant_num;
		btcoexist->board_info.btdm_ant_num = ant_num;
	} else if (BT_COEX_ANT_TYPE_ANTDIV == type) {
		btcoexist->board_info.btdm_ant_num = ant_num;
	} else if (type == BT_COEX_ANT_TYPE_DETECTED) {
		btcoexist->board_info.btdm_ant_num = ant_num;
		if (rtlpriv->cfg->mod_params->ant_sel == 1)
			btcoexist->board_info.btdm_ant_pos =
				BTC_ANTENNA_AT_AUX_PORT;
		else
			btcoexist->board_info.btdm_ant_pos =
				BTC_ANTENNA_AT_MAIN_PORT;
	}
}