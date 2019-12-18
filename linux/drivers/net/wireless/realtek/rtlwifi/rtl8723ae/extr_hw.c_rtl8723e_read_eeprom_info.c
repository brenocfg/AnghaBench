#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int* rfpath_rxenable; } ;
struct rtl_phy {int dummy; } ;
struct rtl_priv {TYPE_2__ dm; TYPE_1__* cfg; struct rtl_phy phy; } ;
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct rtl_efuse {int autoload_failflag; int /*<<< orphan*/  epromtype; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * maps; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  EEPROM_93C46 ; 
 int /*<<< orphan*/  EEPROM_BOOT_EFUSE ; 
 int EFUSE_SEL (int /*<<< orphan*/ ) ; 
 int EFUSE_SEL_MASK ; 
 size_t EFUSE_TEST ; 
 int /*<<< orphan*/  EFUSE_WIFI_SEL_0 ; 
 int /*<<< orphan*/  REG_9346CR ; 
 scalar_t__ RF_1T1R ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _rtl8723e_hal_customized_behavior (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8723e_read_adapter_info (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  _rtl8723e_read_chip_version (struct ieee80211_hw*) ; 
 scalar_t__ get_rf_type (struct rtl_phy*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl8723e_read_eeprom_info(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 tmp_u1b;
	u32 value32;

	value32 = rtl_read_dword(rtlpriv, rtlpriv->cfg->maps[EFUSE_TEST]);
	value32 = (value32 & ~EFUSE_SEL_MASK) | EFUSE_SEL(EFUSE_WIFI_SEL_0);
	rtl_write_dword(rtlpriv, rtlpriv->cfg->maps[EFUSE_TEST], value32);

	rtlhal->version = _rtl8723e_read_chip_version(hw);

	if (get_rf_type(rtlphy) == RF_1T1R)
		rtlpriv->dm.rfpath_rxenable[0] = true;
	else
		rtlpriv->dm.rfpath_rxenable[0] =
		    rtlpriv->dm.rfpath_rxenable[1] = true;
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "VersionID = 0x%4x\n",
						rtlhal->version);

	tmp_u1b = rtl_read_byte(rtlpriv, REG_9346CR);
	if (tmp_u1b & BIT(4)) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG, "Boot from EEPROM\n");
		rtlefuse->epromtype = EEPROM_93C46;
	} else {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG, "Boot from EFUSE\n");
		rtlefuse->epromtype = EEPROM_BOOT_EFUSE;
	}
	if (tmp_u1b & BIT(5)) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "Autoload OK\n");
		rtlefuse->autoload_failflag = false;
		_rtl8723e_read_adapter_info(hw, false);
	} else {
		rtlefuse->autoload_failflag = true;
		_rtl8723e_read_adapter_info(hw, false);
		pr_err("Autoload ERR!!\n");
	}
	_rtl8723e_hal_customized_behavior(hw);
}