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
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,int*) ;struct rtl_priv* adapter; } ;

/* Variables and functions */
 int BIT0 ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int,int*) ; 

__attribute__((used)) static void btc8821a2ant_set_sw_penalty_tx_rate_adaptive(
		struct btc_coexist *btcoexist, bool low_penalty_ra)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[6] = {0};

	h2c_parameter[0] = 0x6;	/* opCode, 0x6 = Retry_Penalty */

	if (low_penalty_ra) {
		h2c_parameter[1] |= BIT0;
		/* normal rate except MCS7/6/5, OFDM54/48/36 */
		h2c_parameter[2] = 0x00;
		/* MCS7 or OFDM54 */
		h2c_parameter[3] = 0xf5;
		/* MCS6 or OFDM48 */
		h2c_parameter[4] = 0xa0;
		/* MCS5 or OFDM36 */
		h2c_parameter[5] = 0xa0;
	}

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], set WiFi Low-Penalty Retry: %s",
		 (low_penalty_ra ? "ON!!" : "OFF!!"));

	btcoexist->btc_fill_h2c(btcoexist, 0x69, 6, h2c_parameter);
}