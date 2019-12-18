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
struct rtl_hal {scalar_t__ hw_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ASPM_L1_LATENCY ; 
 int BIT (int) ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 scalar_t__ HARDWARE_TYPE_RTL8821AE ; 
 int _rtl8821ae_dbi_read (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  _rtl8821ae_dbi_write (struct rtl_priv*,int,int) ; 
 int _rtl8821ae_mdio_read (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  _rtl8821ae_mdio_write (struct rtl_priv*,int,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8821ae_enable_aspm_back_door(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 tmp;

	if (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) {
		if (_rtl8821ae_mdio_read(rtlpriv, 0x04) != 0x8544)
			_rtl8821ae_mdio_write(rtlpriv, 0x04, 0x8544);

		if (_rtl8821ae_mdio_read(rtlpriv, 0x0b) != 0x0070)
			_rtl8821ae_mdio_write(rtlpriv, 0x0b, 0x0070);
	}

	tmp = _rtl8821ae_dbi_read(rtlpriv, 0x70f);
	_rtl8821ae_dbi_write(rtlpriv, 0x70f, tmp | BIT(7) |
			     ASPM_L1_LATENCY << 3);

	tmp = _rtl8821ae_dbi_read(rtlpriv, 0x719);
	_rtl8821ae_dbi_write(rtlpriv, 0x719, tmp | BIT(3) | BIT(4));

	if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) {
		tmp  = _rtl8821ae_dbi_read(rtlpriv, 0x718);
		_rtl8821ae_dbi_write(rtlpriv, 0x718, tmp|BIT(4));
	}
}