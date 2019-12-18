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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_read_1byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_read_4byte ) (struct btc_coexist*,int) ;struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8723b2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8723b2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8723b2ant_sw_mechanism (struct btc_coexist*,int,int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int) ; 

__attribute__((used)) static void btc8723b2ant_action_wifi_link_process(struct btc_coexist
						     *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u32 u32tmp;
	u8 u8tmpa, u8tmpb;

	btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 15);
	btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);

	btc8723b2ant_sw_mechanism(btcoexist, false, false, false, false);

	u32tmp = btcoexist->btc_read_4byte(btcoexist, 0x948);
	u8tmpa = btcoexist->btc_read_1byte(btcoexist, 0x765);
	u8tmpb = btcoexist->btc_read_1byte(btcoexist, 0x76e);

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], 0x948 = 0x%x, 0x765 = 0x%x, 0x76e = 0x%x\n",
		 u32tmp, u8tmpa, u8tmpb);
}