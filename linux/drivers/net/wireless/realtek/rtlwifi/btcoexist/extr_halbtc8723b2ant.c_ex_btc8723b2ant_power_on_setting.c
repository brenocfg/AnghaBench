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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct btc_board_info {int single_ant_path; void* btdm_ant_pos; } ;
struct btc_coexist {int (* btc_read_2byte ) (struct btc_coexist*,int) ;scalar_t__ chip_interface; int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* btc_write_4byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_write_2byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;struct btc_board_info board_info; } ;

/* Variables and functions */
 int BIT0 ; 
 int BIT1 ; 
 void* BTC_ANTENNA_AT_AUX_PORT ; 
 void* BTC_ANTENNA_AT_MAIN_PORT ; 
 scalar_t__ BTC_INTF_USB ; 
 int /*<<< orphan*/  BTC_SET_ACT_ANTPOSREGRISTRY_CTRL ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int) ; 
 int stub2 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ex_btc8723b2ant_power_on_setting(struct btc_coexist *btcoexist)
{
	struct btc_board_info *board_info = &btcoexist->board_info;
	u16 u16tmp = 0x0;
	u32 value = 0;

	btcoexist->btc_write_1byte(btcoexist, 0x67, 0x20);

	/* enable BB, REG_SYS_FUNC_EN such that we can write 0x948 correctly */
	u16tmp = btcoexist->btc_read_2byte(btcoexist, 0x2);
	btcoexist->btc_write_2byte(btcoexist, 0x2, u16tmp | BIT0 | BIT1);

	btcoexist->btc_write_4byte(btcoexist, 0x948, 0x0);

	if (btcoexist->chip_interface == BTC_INTF_USB) {
		/* fixed at S0 for USB interface */
		board_info->btdm_ant_pos = BTC_ANTENNA_AT_AUX_PORT;
	} else {
		/* for PCIE and SDIO interface, we check efuse 0xc3[6] */
		if (board_info->single_ant_path == 0) {
			/* set to S1 */
			board_info->btdm_ant_pos = BTC_ANTENNA_AT_MAIN_PORT;
		} else if (board_info->single_ant_path == 1) {
			/* set to S0 */
			board_info->btdm_ant_pos = BTC_ANTENNA_AT_AUX_PORT;
		}
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_ANTPOSREGRISTRY_CTRL,
				   &value);
	}
}