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
struct btc_board_info {scalar_t__ btdm_ant_pos; } ;
struct btc_coexist {int (* btc_read_4byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_write_2byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;int /*<<< orphan*/  (* btc_write_4byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,int*) ;int /*<<< orphan*/  (* btc_set_rf_reg ) (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct btc_board_info board_info; } ;

/* Variables and functions */
 int BIT23 ; 
 int BIT24 ; 
 scalar_t__ BTC_ANTENNA_AT_MAIN_PORT ; 
#define  BTC_ANT_WIFI_AT_AUX 129 
#define  BTC_ANT_WIFI_AT_MAIN 128 
 int /*<<< orphan*/  BTC_GET_BL_EXT_SWITCH ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_FW_VER ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub11 (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub12 (struct btc_coexist*,int,int,int*) ; 
 int /*<<< orphan*/  stub13 (struct btc_coexist*,int,int,int*) ; 
 int /*<<< orphan*/  stub14 (struct btc_coexist*,int,int) ; 
 int stub15 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub16 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub17 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub18 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub19 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub20 (struct btc_coexist*,int,int,int) ; 
 int stub21 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub22 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub23 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub24 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub25 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int,int,int*) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int,int) ; 

__attribute__((used)) static void btc8723b2ant_set_ant_path(struct btc_coexist *btcoexist,
				      u8 antpos_type, bool init_hwcfg,
				      bool wifi_off)
{
	struct btc_board_info *board_info = &btcoexist->board_info;
	u32 fw_ver = 0, u32tmp = 0;
	bool pg_ext_switch = false;
	bool use_ext_switch = false;
	u8 h2c_parameter[2] = {0};

	btcoexist->btc_get(btcoexist, BTC_GET_BL_EXT_SWITCH, &pg_ext_switch);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);

	if ((fw_ver < 0xc0000) || pg_ext_switch)
		use_ext_switch = true;

	if (init_hwcfg) {
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x39, 0x8, 0x1);
		btcoexist->btc_write_1byte(btcoexist, 0x974, 0xff);
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x944, 0x3, 0x3);
		btcoexist->btc_write_1byte(btcoexist, 0x930, 0x77);
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x67, 0x20, 0x1);

		if (fw_ver >= 0x180000) {
			/* Use H2C to set GNT_BT to High to avoid A2DP click */
			h2c_parameter[0] = 1;
			btcoexist->btc_fill_h2c(btcoexist, 0x6E, 1,
						h2c_parameter);
		} else {
			btcoexist->btc_write_1byte(btcoexist, 0x765, 0x18);
		}

		btcoexist->btc_write_4byte(btcoexist, 0x948, 0x0);

		/* WiFi TRx Mask off */
		btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A,
					  0x1, 0xfffff, 0x0);

		if (board_info->btdm_ant_pos == BTC_ANTENNA_AT_MAIN_PORT) {
			/* tell firmware "no antenna inverse" */
			h2c_parameter[0] = 0;
		} else {
			/* tell firmware "antenna inverse" */
			h2c_parameter[0] = 1;
		}

		if (use_ext_switch) {
			/* ext switch type */
			h2c_parameter[1] = 1;
		} else {
			/* int switch type */
			h2c_parameter[1] = 0;
		}
		btcoexist->btc_fill_h2c(btcoexist, 0x65, 2, h2c_parameter);
	} else {
		if (fw_ver >= 0x180000) {
			/* Use H2C to set GNT_BT to "Control by PTA"*/
			h2c_parameter[0] = 0;
			btcoexist->btc_fill_h2c(btcoexist, 0x6E, 1,
						h2c_parameter);
		} else {
			btcoexist->btc_write_1byte(btcoexist, 0x765, 0x0);
		}
	}

	/* ext switch setting */
	if (use_ext_switch) {
		if (init_hwcfg) {
			/* 0x4c[23] = 0, 0x4c[24] = 1 Ant controlled by WL/BT */
			u32tmp = btcoexist->btc_read_4byte(btcoexist, 0x4c);
			u32tmp &= ~BIT23;
			u32tmp |= BIT24;
			btcoexist->btc_write_4byte(btcoexist, 0x4c, u32tmp);
		}

		/* fixed internal switch S1->WiFi, S0->BT */
		if (board_info->btdm_ant_pos == BTC_ANTENNA_AT_MAIN_PORT)
			btcoexist->btc_write_2byte(btcoexist, 0x948, 0x0);
		else
			btcoexist->btc_write_2byte(btcoexist, 0x948, 0x280);

		switch (antpos_type) {
		case BTC_ANT_WIFI_AT_MAIN:
			/* ext switch main at wifi */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x92c,
							   0x3, 0x1);
			break;
		case BTC_ANT_WIFI_AT_AUX:
			/* ext switch aux at wifi */
			btcoexist->btc_write_1byte_bitmask(btcoexist,
							   0x92c, 0x3, 0x2);
			break;
		}
	} else {
		/* internal switch */
		if (init_hwcfg) {
			/* 0x4c[23] = 0, 0x4c[24] = 1 Ant controlled by WL/BT */
			u32tmp = btcoexist->btc_read_4byte(btcoexist, 0x4c);
			u32tmp |= BIT23;
			u32tmp &= ~BIT24;
			btcoexist->btc_write_4byte(btcoexist, 0x4c, u32tmp);
		}

		/* fixed ext switch, S1->Main, S0->Aux */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x64, 0x1, 0x0);
		switch (antpos_type) {
		case BTC_ANT_WIFI_AT_MAIN:
			/* fixed internal switch S1->WiFi, S0->BT */
			btcoexist->btc_write_2byte(btcoexist, 0x948, 0x0);
			break;
		case BTC_ANT_WIFI_AT_AUX:
			/* fixed internal switch S0->WiFi, S1->BT */
			btcoexist->btc_write_2byte(btcoexist, 0x948, 0x280);
			break;
		}
	}
}