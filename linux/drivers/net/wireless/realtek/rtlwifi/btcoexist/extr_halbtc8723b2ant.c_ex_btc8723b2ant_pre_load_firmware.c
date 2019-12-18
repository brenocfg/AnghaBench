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
struct btc_board_info {int single_ant_path; } ;
struct btc_coexist {scalar_t__ chip_interface; int /*<<< orphan*/  (* btc_write_local_reg_1byte ) (struct btc_coexist*,int,int) ;struct btc_board_info board_info; } ;

/* Variables and functions */
 scalar_t__ BTC_INTF_PCI ; 
 scalar_t__ BTC_INTF_SDIO ; 
 scalar_t__ BTC_INTF_USB ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 

void ex_btc8723b2ant_pre_load_firmware(struct btc_coexist *btcoexist)
{
	struct btc_board_info *board_info = &btcoexist->board_info;
	u8 u8tmp = 0x4; /* Set BIT2 by default since it's 2ant case */

	/**
	 * S0 or S1 setting and Local register setting(By this fw can get
	 * ant number, S0/S1, ... info)
	 *
	 * Local setting bit define
	 *	BIT0: "0" : no antenna inverse; "1" : antenna inverse
	 *	BIT1: "0" : internal switch; "1" : external switch
	 *	BIT2: "0" : one antenna; "1" : two antennas
	 *
	 * NOTE: here default all internal switch and 1-antenna ==> BIT1=0 and
	 * BIT2 = 0
	 */
	if (btcoexist->chip_interface == BTC_INTF_USB) {
		/* fixed at S0 for USB interface */
		u8tmp |= 0x1; /* antenna inverse */
		btcoexist->btc_write_local_reg_1byte(btcoexist, 0xfe08, u8tmp);
	} else {
		/* for PCIE and SDIO interface, we check efuse 0xc3[6] */
		if (board_info->single_ant_path == 0) {
		} else if (board_info->single_ant_path == 1) {
			/* set to S0 */
			u8tmp |= 0x1; /* antenna inverse */
		}

		if (btcoexist->chip_interface == BTC_INTF_PCI)
			btcoexist->btc_write_local_reg_1byte(btcoexist, 0x384,
							     u8tmp);
		else if (btcoexist->chip_interface == BTC_INTF_SDIO)
			btcoexist->btc_write_local_reg_1byte(btcoexist, 0x60,
							     u8tmp);
	}
}