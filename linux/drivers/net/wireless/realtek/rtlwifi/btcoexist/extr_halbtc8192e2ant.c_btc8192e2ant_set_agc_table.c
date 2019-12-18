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
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_write_4byte ) (struct btc_coexist*,int,int) ;struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub11 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub12 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int,int) ; 

__attribute__((used)) static void btc8192e2ant_set_agc_table(struct btc_coexist *btcoexist,
				       bool agc_table_en)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	/* BB AGC Gain Table */
	if (agc_table_en) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BB Agc Table On!\n");
		btcoexist->btc_write_4byte(btcoexist, 0xc78, 0x0a1A0001);
		btcoexist->btc_write_4byte(btcoexist, 0xc78, 0x091B0001);
		btcoexist->btc_write_4byte(btcoexist, 0xc78, 0x081C0001);
		btcoexist->btc_write_4byte(btcoexist, 0xc78, 0x071D0001);
		btcoexist->btc_write_4byte(btcoexist, 0xc78, 0x061E0001);
		btcoexist->btc_write_4byte(btcoexist, 0xc78, 0x051F0001);
	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BB Agc Table Off!\n");
		btcoexist->btc_write_4byte(btcoexist, 0xc78, 0xaa1A0001);
		btcoexist->btc_write_4byte(btcoexist, 0xc78, 0xa91B0001);
		btcoexist->btc_write_4byte(btcoexist, 0xc78, 0xa81C0001);
		btcoexist->btc_write_4byte(btcoexist, 0xc78, 0xa71D0001);
		btcoexist->btc_write_4byte(btcoexist, 0xc78, 0xa61E0001);
		btcoexist->btc_write_4byte(btcoexist, 0xc78, 0xa51F0001);
	}
}