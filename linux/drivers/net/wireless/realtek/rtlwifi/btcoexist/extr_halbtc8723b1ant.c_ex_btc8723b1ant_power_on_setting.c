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
typedef  int u32 ;
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct btc_board_info {int single_ant_path; void* btdm_ant_pos; } ;
struct btc_coexist {int stop_coex_dm; int (* btc_read_2byte ) (struct btc_coexist*,int) ;scalar_t__ chip_interface; int /*<<< orphan*/  (* btc_write_local_reg_1byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* btc_write_4byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_write_2byte ) (struct btc_coexist*,int,int) ;struct btc_board_info board_info; struct rtl_priv* adapter; } ;

/* Variables and functions */
 int BIT0 ; 
 int BIT1 ; 
 void* BTC_ANTENNA_AT_AUX_PORT ; 
 void* BTC_ANTENNA_AT_MAIN_PORT ; 
 scalar_t__ BTC_INTF_PCI ; 
 scalar_t__ BTC_INTF_SDIO ; 
 scalar_t__ BTC_INTF_USB ; 
 int /*<<< orphan*/  BTC_SET_ACT_ANTPOSREGRISTRY_CTRL ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub11 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub12 (struct btc_coexist*,int,int) ; 
 int stub2 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int,int) ; 

void ex_btc8723b1ant_power_on_setting(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_board_info *board_info = &btcoexist->board_info;
	u8 u8tmp = 0x0;
	u16 u16tmp = 0x0;
	u32 value;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "xxxxxxxxxxxxxxxx Execute 8723b 1-Ant PowerOn Setting xxxxxxxxxxxxxxxx!!\n");

	btcoexist->stop_coex_dm = true;

	btcoexist->btc_write_1byte(btcoexist, 0x67, 0x20);

	/* enable BB, REG_SYS_FUNC_EN such that we can write 0x948 correctly. */
	u16tmp = btcoexist->btc_read_2byte(btcoexist, 0x2);
	btcoexist->btc_write_2byte(btcoexist, 0x2, u16tmp | BIT0 | BIT1);

	/* set GRAN_BT = 1 */
	btcoexist->btc_write_1byte(btcoexist, 0x765, 0x18);
	/* set WLAN_ACT = 0 */
	btcoexist->btc_write_1byte(btcoexist, 0x76e, 0x4);

	/* S0 or S1 setting and Local register setting(By the setting fw can get
	 * ant number, S0/S1, ... info)
	 *
	 * Local setting bit define
	 *	BIT0: "0" for no antenna inverse; "1" for antenna inverse
	 *	BIT1: "0" for internal switch; "1" for external switch
	 *	BIT2: "0" for one antenna; "1" for two antenna
	 * NOTE: here default all internal switch and 1-antenna ==> BIT1=0 and
	 * BIT2 = 0
	 */
	if (btcoexist->chip_interface == BTC_INTF_USB) {
		/* fixed at S0 for USB interface */
		btcoexist->btc_write_4byte(btcoexist, 0x948, 0x0);

		u8tmp |= 0x1; /* antenna inverse */
		btcoexist->btc_write_local_reg_1byte(btcoexist, 0xfe08, u8tmp);

		board_info->btdm_ant_pos = BTC_ANTENNA_AT_AUX_PORT;
	} else {
		/* for PCIE and SDIO interface, we check efuse 0xc3[6] */
		if (board_info->single_ant_path == 0) {
			/* set to S1 */
			btcoexist->btc_write_4byte(btcoexist, 0x948, 0x280);
			board_info->btdm_ant_pos = BTC_ANTENNA_AT_MAIN_PORT;
			value = 1;
		} else if (board_info->single_ant_path == 1) {
			/* set to S0 */
			btcoexist->btc_write_4byte(btcoexist, 0x948, 0x0);
			u8tmp |= 0x1; /* antenna inverse */
			board_info->btdm_ant_pos = BTC_ANTENNA_AT_AUX_PORT;
			value = 0;
		}

		btcoexist->btc_set(btcoexist, BTC_SET_ACT_ANTPOSREGRISTRY_CTRL,
				   &value);

		if (btcoexist->chip_interface == BTC_INTF_PCI)
			btcoexist->btc_write_local_reg_1byte(btcoexist, 0x384,
							     u8tmp);
		else if (btcoexist->chip_interface == BTC_INTF_SDIO)
			btcoexist->btc_write_local_reg_1byte(btcoexist, 0x60,
							     u8tmp);
	}
}