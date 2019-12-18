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
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_set_rf_reg ) (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ;scalar_t__ initilized; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int bt_rf0x1e_backup; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_RF_A ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void btc8192e2ant_set_sw_rf_rx_lpf_corner(struct btc_coexist *btcoexist,
						 bool rx_rf_shrink_on)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	if (rx_rf_shrink_on) {
		/* Shrink RF Rx LPF corner */
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Shrink RF Rx LPF corner!!\n");
		btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1e,
					  0xfffff, 0xffffc);
	} else {
		/* Resume RF Rx LPF corner
		 * After initialized, we can use coex_dm->btRf0x1eBackup
		 */
		if (btcoexist->initilized) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Resume RF Rx LPF corner!!\n");
			btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1e,
						  0xfffff,
						  coex_dm->bt_rf0x1e_backup);
		}
	}
}