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
struct rtl_priv {int dummy; } ;
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct rtl_efuse {int autoload_failflag; int /*<<< orphan*/  epromtype; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BOOT_FROM_EEPROM ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  EEPROM_93C46 ; 
 int /*<<< orphan*/  EEPROM_BOOT_EFUSE ; 
 int EEPROM_EN ; 
 int /*<<< orphan*/  IS_NORMAL_CHIP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_9346CR ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  _rtl92cu_hal_customized_behavior (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92cu_read_adapter_info (struct ieee80211_hw*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 

void rtl92cu_read_eeprom_info(struct ieee80211_hw *hw)
{

	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 tmp_u1b;

	if (!IS_NORMAL_CHIP(rtlhal->version))
		return;
	tmp_u1b = rtl_read_byte(rtlpriv, REG_9346CR);
	rtlefuse->epromtype = (tmp_u1b & BOOT_FROM_EEPROM) ?
			       EEPROM_93C46 : EEPROM_BOOT_EFUSE;
	RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG, "Boot from %s\n",
		 tmp_u1b & BOOT_FROM_EEPROM ? "EERROM" : "EFUSE");
	rtlefuse->autoload_failflag = (tmp_u1b & EEPROM_EN) ? false : true;
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "Autoload %s\n",
		 tmp_u1b & EEPROM_EN ? "OK!!" : "ERR!!");
	_rtl92cu_read_adapter_info(hw);
	_rtl92cu_hal_customized_behavior(hw);
	return;
}