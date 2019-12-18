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
typedef  int u32 ;
struct btc_coexist {int (* btc_read_4byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;} ;
struct TYPE_2__ {int high_priority_tx; int high_priority_rx; int low_priority_tx; int low_priority_rx; } ;

/* Variables and functions */
 int MASKHWORD ; 
 int MASKLWORD ; 
 TYPE_1__* coex_sta ; 
 int stub1 (struct btc_coexist*,int) ; 
 int stub2 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int) ; 

__attribute__((used)) static void btc8821a1ant_monitor_bt_ctr(struct btc_coexist *btcoexist)
{
	u32 reg_hp_tx_rx, reg_lp_tx_rx, u4_tmp;
	u32 reg_hp_tx = 0, reg_hp_rx = 0, reg_lp_tx = 0, reg_lp_rx = 0;

	reg_hp_tx_rx = 0x770;
	reg_lp_tx_rx = 0x774;

	u4_tmp = btcoexist->btc_read_4byte(btcoexist, reg_hp_tx_rx);
	reg_hp_tx = u4_tmp & MASKLWORD;
	reg_hp_rx = (u4_tmp & MASKHWORD) >> 16;

	u4_tmp = btcoexist->btc_read_4byte(btcoexist, reg_lp_tx_rx);
	reg_lp_tx = u4_tmp & MASKLWORD;
	reg_lp_rx = (u4_tmp & MASKHWORD) >> 16;

	coex_sta->high_priority_tx = reg_hp_tx;
	coex_sta->high_priority_rx = reg_hp_rx;
	coex_sta->low_priority_tx = reg_lp_tx;
	coex_sta->low_priority_rx = reg_lp_rx;

	/* reset counter */
	btcoexist->btc_write_1byte(btcoexist, 0x76e, 0xc);
}