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
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,int*) ;int /*<<< orphan*/  (* btc_set_rf_reg ) (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_IS_IN_MP_MODE ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_FW_VER ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void btc8723b2ant_wifioff_hwcfg(struct btc_coexist *btcoexist)
{
	bool is_in_mp_mode = false;
	u8 h2c_parameter[2] = {0};
	u32 fw_ver = 0;

	/* set wlan_act to low */
	btcoexist->btc_write_1byte(btcoexist, 0x76e, 0x4);

	/* WiFi standby while GNT_BT 0 -> 1 */
	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x780);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
	if (fw_ver >= 0x180000) {
		/* Use H2C to set GNT_BT to HIGH */
		h2c_parameter[0] = 1;
		btcoexist->btc_fill_h2c(btcoexist, 0x6E, 1, h2c_parameter);
	} else {
		btcoexist->btc_write_1byte(btcoexist, 0x765, 0x18);
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_IS_IN_MP_MODE,
			   &is_in_mp_mode);
	if (!is_in_mp_mode)
		/* BT select s0/s1 is controlled by BT */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x67, 0x20, 0x0);
	else
		/* BT select s0/s1 is controlled by WiFi */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x67, 0x20, 0x1);
}