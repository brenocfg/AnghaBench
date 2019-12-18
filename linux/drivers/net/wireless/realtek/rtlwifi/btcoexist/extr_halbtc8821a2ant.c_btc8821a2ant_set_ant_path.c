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
struct btc_coexist {int (* btc_read_4byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,int*) ;int /*<<< orphan*/  (* btc_write_4byte ) (struct btc_coexist*,int,int) ;struct btc_board_info board_info; } ;

/* Variables and functions */
 int BIT23 ; 
 int BIT24 ; 
 scalar_t__ BTC_ANTENNA_AT_MAIN_PORT ; 
#define  BTC_ANT_WIFI_AT_AUX 129 
#define  BTC_ANT_WIFI_AT_MAIN 128 
 int stub1 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int,int*) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void btc8821a2ant_set_ant_path(struct btc_coexist *btcoexist,
				      u8 ant_pos_type, bool init_hw_cfg,
				      bool wifi_off)
{
	struct btc_board_info *board_info = &btcoexist->board_info;
	u32 u4tmp = 0;
	u8 h2c_parameter[2] = {0};

	if (init_hw_cfg) {
		/*  0x4c[23] = 0, 0x4c[24] = 1  Antenna control by WL/BT */
		u4tmp = btcoexist->btc_read_4byte(btcoexist, 0x4c);
		u4tmp &= ~BIT23;
		u4tmp |= BIT24;
		btcoexist->btc_write_4byte(btcoexist, 0x4c, u4tmp);

		btcoexist->btc_write_4byte(btcoexist, 0x974, 0x3ff);

		if (board_info->btdm_ant_pos == BTC_ANTENNA_AT_MAIN_PORT) {
			/* tell firmware "antenna inverse"  ==> WRONG firmware
			 * antenna control code ==>need fw to fix
			 */
			h2c_parameter[0] = 1;
			h2c_parameter[1] = 1;
			btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
						h2c_parameter);
		} else {
			/* tell firmware "no antenna inverse" ==> WRONG firmware
			 * antenna control code ==>need fw to fix
			 */
			h2c_parameter[0] = 0;
			h2c_parameter[1] = 1;
			btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
						h2c_parameter);
		}
	}

	/* ext switch setting */
	switch (ant_pos_type) {
	case BTC_ANT_WIFI_AT_MAIN:
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcb7, 0x30, 0x1);
		break;
	case BTC_ANT_WIFI_AT_AUX:
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcb7, 0x30, 0x2);
		break;
	}
}