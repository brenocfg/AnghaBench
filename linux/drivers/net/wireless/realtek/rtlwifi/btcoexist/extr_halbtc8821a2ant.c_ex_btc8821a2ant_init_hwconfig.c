#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int (* btc_read_1byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_get_rf_reg ) (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ;struct rtl_priv* adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  bt_rf0x1e_backup; } ;
struct TYPE_3__ {scalar_t__ dis_ver_info_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_WIFI_AT_MAIN ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btc8821a2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a2ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int,int,int) ; 

void ex_btc8821a2ant_init_hwconfig(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 u1tmp = 0;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], 2Ant Init HW Config!!\n");

	/* backup rf 0x1e value */
	coex_dm->bt_rf0x1e_backup =
		btcoexist->btc_get_rf_reg(btcoexist, BTC_RF_A, 0x1e, 0xfffff);

	/* 0x790[5:0] = 0x5 */
	u1tmp = btcoexist->btc_read_1byte(btcoexist, 0x790);
	u1tmp &= 0xc0;
	u1tmp |= 0x5;
	btcoexist->btc_write_1byte(btcoexist, 0x790, u1tmp);

	/* Antenna config */
	btc8821a2ant_set_ant_path(btcoexist, BTC_ANT_WIFI_AT_MAIN, true, false);
	coex_sta->dis_ver_info_cnt = 0;

	/* PTA parameter */
	btc8821a2ant_coex_table_with_type(btcoexist, FORCE_EXEC, 0);

	/* Enable counter statistics */
	/* 0x76e[3] = 1, WLAN_Act control by PTA */
	btcoexist->btc_write_1byte(btcoexist, 0x76e, 0x4);
	btcoexist->btc_write_1byte(btcoexist, 0x778, 0x3);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x40, 0x20, 0x1);
}