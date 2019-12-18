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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PS_STATE_RF_OFF_LOW_PWR ; 
 int /*<<< orphan*/  _rtl92ee_set_fw_clock_off (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl92ee_set_fw_ps_rf_off_low_power(struct ieee80211_hw *hw)
{
	u8 rpwm_val = 0;

	rpwm_val |= FW_PS_STATE_RF_OFF_LOW_PWR;
	_rtl92ee_set_fw_clock_off(hw, rpwm_val);
}