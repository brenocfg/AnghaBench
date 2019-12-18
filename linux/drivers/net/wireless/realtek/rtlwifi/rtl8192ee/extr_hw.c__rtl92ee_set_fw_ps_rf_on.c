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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int FW_PS_ACK ; 
 int FW_PS_STATE_RF_OFF_92E ; 
 int /*<<< orphan*/  _rtl92ee_set_fw_clock_on (struct ieee80211_hw*,int,int) ; 

__attribute__((used)) static void _rtl92ee_set_fw_ps_rf_on(struct ieee80211_hw *hw)
{
	u8 rpwm_val = 0;

	rpwm_val |= (FW_PS_STATE_RF_OFF_92E | FW_PS_ACK);
	_rtl92ee_set_fw_clock_on(hw, rpwm_val, true);
}