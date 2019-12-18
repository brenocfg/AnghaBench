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
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* btc_write_4byte ) (struct btc_coexist*,int,int /*<<< orphan*/ ) ;struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc8821a2ant_set_coex_table(struct btc_coexist *btcoexist,
					u32 val0x6c0, u32 val0x6c4,
					u32 val0x6c8, u8 val0x6cc)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], set coex table, set 0x6c0 = 0x%x\n", val0x6c0);
	btcoexist->btc_write_4byte(btcoexist, 0x6c0, val0x6c0);

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], set coex table, set 0x6c4 = 0x%x\n", val0x6c4);
	btcoexist->btc_write_4byte(btcoexist, 0x6c4, val0x6c4);

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], set coex table, set 0x6c8 = 0x%x\n", val0x6c8);
	btcoexist->btc_write_4byte(btcoexist, 0x6c8, val0x6c8);

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], set coex table, set 0x6cc = 0x%x\n", val0x6cc);
	btcoexist->btc_write_1byte(btcoexist, 0x6cc, val0x6cc);
}