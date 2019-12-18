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
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,int*) ;struct rtl_priv* adapter; } ;
struct TYPE_2__ {int* ps_tdma_para; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int,int*) ; 

__attribute__((used)) static void btc8192e2ant_set_fw_ps_tdma(struct btc_coexist *btcoexist, u8 byte1,
					u8 byte2, u8 byte3, u8 byte4, u8 byte5)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	u8 h2c_parameter[5] = {0};

	h2c_parameter[0] = byte1;
	h2c_parameter[1] = byte2;
	h2c_parameter[2] = byte3;
	h2c_parameter[3] = byte4;
	h2c_parameter[4] = byte5;

	coex_dm->ps_tdma_para[0] = byte1;
	coex_dm->ps_tdma_para[1] = byte2;
	coex_dm->ps_tdma_para[2] = byte3;
	coex_dm->ps_tdma_para[3] = byte4;
	coex_dm->ps_tdma_para[4] = byte5;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], FW write 0x60(5bytes) = 0x%x%08x\n",
		 h2c_parameter[0],
		 h2c_parameter[1] << 24 | h2c_parameter[2] << 16 |
		 h2c_parameter[3] << 8 | h2c_parameter[4]);

	btcoexist->btc_fill_h2c(btcoexist, 0x60, 5, h2c_parameter);
}