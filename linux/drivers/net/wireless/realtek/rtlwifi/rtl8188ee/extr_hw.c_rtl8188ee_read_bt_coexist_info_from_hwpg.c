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
typedef  int u8 ;
struct TYPE_2__ {int eeprom_bt_coexist; int eeprom_bt_type; int eeprom_bt_ant_num; int eeprom_bt_ant_isol; int eeprom_bt_radio_shared; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ANT_X2 ; 
 int BT_2WIRE ; 
 int BT_RADIO_SHARED ; 
 size_t EEPROM_RF_BT_SETTING_88E ; 
 size_t EEPROM_RF_FEATURE_OPTION_88E ; 
 int /*<<< orphan*/  rtl8188ee_bt_var_init (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8188ee_read_bt_coexist_info_from_hwpg(struct ieee80211_hw *hw,
					      bool auto_load_fail, u8 *hwinfo)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 value;

	if (!auto_load_fail) {
		rtlpriv->btcoexist.eeprom_bt_coexist =
			((hwinfo[EEPROM_RF_FEATURE_OPTION_88E] & 0xe0) >> 5);
		if (hwinfo[EEPROM_RF_FEATURE_OPTION_88E] == 0xFF)
			rtlpriv->btcoexist.eeprom_bt_coexist  = 0;
		value = hwinfo[EEPROM_RF_BT_SETTING_88E];
		rtlpriv->btcoexist.eeprom_bt_type = ((value & 0xe) >> 1);
		rtlpriv->btcoexist.eeprom_bt_ant_num = (value & 0x1);
		rtlpriv->btcoexist.eeprom_bt_ant_isol = ((value & 0x10) >> 4);
		rtlpriv->btcoexist.eeprom_bt_radio_shared =
				 ((value & 0x20) >> 5);
	} else {
		rtlpriv->btcoexist.eeprom_bt_coexist = 0;
		rtlpriv->btcoexist.eeprom_bt_type = BT_2WIRE;
		rtlpriv->btcoexist.eeprom_bt_ant_num = ANT_X2;
		rtlpriv->btcoexist.eeprom_bt_ant_isol = 0;
		rtlpriv->btcoexist.eeprom_bt_radio_shared = BT_RADIO_SHARED;
	}

	rtl8188ee_bt_var_init(hw);
}