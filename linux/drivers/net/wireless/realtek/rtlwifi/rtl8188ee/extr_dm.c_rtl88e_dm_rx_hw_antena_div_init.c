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
typedef  int u32 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DM_REG_ANTDIV_PARA1_11N ; 
 int /*<<< orphan*/  DM_REG_ANTSEL_PIN_11N ; 
 int /*<<< orphan*/  DM_REG_ANT_MAPPING1_11N ; 
 int /*<<< orphan*/  DM_REG_BB_PWR_SAV4_11N ; 
 int /*<<< orphan*/  DM_REG_CCK_ANTDIV_PARA2_11N ; 
 int /*<<< orphan*/  DM_REG_LNA_SWITCH_11N ; 
 int /*<<< orphan*/  DM_REG_PIN_CTRL_11N ; 
 int /*<<< orphan*/  DM_REG_RX_ANT_CTRL_11N ; 
 int /*<<< orphan*/  MAIN_ANT ; 
 int MASKDWORD ; 
 int MASKLWORD ; 
 int /*<<< orphan*/  rtl88e_dm_update_rx_idle_ant (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl88e_dm_rx_hw_antena_div_init(struct ieee80211_hw *hw)
{
	u32  value32;

	/*MAC Setting*/
	value32 = rtl_get_bbreg(hw, DM_REG_ANTSEL_PIN_11N, MASKDWORD);
	rtl_set_bbreg(hw, DM_REG_ANTSEL_PIN_11N,
		      MASKDWORD, value32 | (BIT(23) | BIT(25)));
	/*Pin Setting*/
	rtl_set_bbreg(hw, DM_REG_PIN_CTRL_11N, BIT(9) | BIT(8), 0);
	rtl_set_bbreg(hw, DM_REG_RX_ANT_CTRL_11N, BIT(10), 0);
	rtl_set_bbreg(hw, DM_REG_LNA_SWITCH_11N, BIT(22), 1);
	rtl_set_bbreg(hw, DM_REG_LNA_SWITCH_11N, BIT(31), 1);
	/*OFDM Setting*/
	rtl_set_bbreg(hw, DM_REG_ANTDIV_PARA1_11N, MASKDWORD, 0x000000a0);
	/*CCK Setting*/
	rtl_set_bbreg(hw, DM_REG_BB_PWR_SAV4_11N, BIT(7), 1);
	rtl_set_bbreg(hw, DM_REG_CCK_ANTDIV_PARA2_11N, BIT(4), 1);
	rtl88e_dm_update_rx_idle_ant(hw, MAIN_ANT);
	rtl_set_bbreg(hw, DM_REG_ANT_MAPPING1_11N, MASKLWORD, 0x0201);
}