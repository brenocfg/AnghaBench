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
struct rtl_efuse {scalar_t__ antenna_div_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ CGCS_RX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_SMART_ANTDIV ; 
 int /*<<< orphan*/  rtl88e_dm_fast_training_init (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl88e_dm_rx_hw_antena_div_init (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl88e_dm_trx_hw_antenna_div_init (struct ieee80211_hw*) ; 
 struct rtl_efuse* rtl_efuse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl88e_dm_antenna_div_init(struct ieee80211_hw *hw)
{
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));

	if (rtlefuse->antenna_div_type == CGCS_RX_HW_ANTDIV)
		rtl88e_dm_rx_hw_antena_div_init(hw);
	else if (rtlefuse->antenna_div_type == CG_TRX_HW_ANTDIV)
		rtl88e_dm_trx_hw_antenna_div_init(hw);
	else if (rtlefuse->antenna_div_type == CG_TRX_SMART_ANTDIV)
		rtl88e_dm_fast_training_init(hw);

}